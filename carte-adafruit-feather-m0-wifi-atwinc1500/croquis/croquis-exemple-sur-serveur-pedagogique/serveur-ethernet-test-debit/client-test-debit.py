#! /usr/bin/env python
# -*- coding: UTF-8 -*-

#——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————*

import socket, numpy, time
from threading import Thread

#——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————*

class Reception (Thread):
  def __init__(self, so, nombreOctetsARecevoir):
    Thread.__init__(self)
    self.so = so
    self.nombreOctetsARecevoir = nombreOctetsARecevoir

  def run (self):
    print ("    Thread de réception")
    boucler = True
    self.bufferReception = bytearray(b" " * self.nombreOctetsARecevoir)
    restentALire = self.nombreOctetsARecevoir
    view = memoryview (self.bufferReception)
    while restentALire > 0 :
      nbytes = so.recv_into (view, restentALire)
      view = view [nbytes:] # slicing views is cheap
      restentALire -= nbytes
    print ("    Fin du thread de réception")

#——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————*

#--- Caractéristiques du serveur
serveurTCP = "192.168.0.14"
port = 16009
#--- Nombre d'octets échangés
TAILLE_BUFFER = 1000 * 1000
#--- Construire le tableau des données à envoyer
bufferEmission = bytearray (b" " * TAILLE_BUFFER)
valeur = 0
for i in range (0, TAILLE_BUFFER) :
  bufferEmission [i] = valeur
  valeur = (valeur + 1) % 256
#--- Noter l'instant de début
instantDebut = time.time ()
#--- Établir la connexion
so = socket.socket (socket.AF_INET, socket.SOCK_STREAM)
so.connect ((serveurTCP, port))
print ("  Connexion sur {}:{}".format (serveurTCP, port))
#--- Créer le thread de réception
threadReception = Reception (so, TAILLE_BUFFER)
threadReception.start ()
#--- Envoyer les données
so.sendall (bufferEmission)
#--- Attente de la fin du thread de réception
threadReception.join ()
#--- Afficher durée et débit
duree = time.time () - instantDebut
print ("Durée " + str (duree) + " s, débit " + str (int (TAILLE_BUFFER / duree / 1000)) + " kio/s")
#--- Fermer la connexion
print ("  Fermeture")
so.shutdown (socket.SHUT_RDWR) # IMPORTANT! Ceci permet aux threads de se terminer
so.close ()
#--- Vérifier que les données reçues sont égales aux données envoyées
ok = True
for i in range (0, TAILLE_BUFFER) :
  if bufferEmission [i] != threadReception.bufferReception [i] :
    print ("  Erreur, envoyé " + str (bufferEmission [i]) + ", reçu " + str (threadReception.bufferReception [i]))
    ok = False
    break
if ok :
  print ("  Données reçues correctes")


#----------------------------------------------------------------------------------------------------------------------*
