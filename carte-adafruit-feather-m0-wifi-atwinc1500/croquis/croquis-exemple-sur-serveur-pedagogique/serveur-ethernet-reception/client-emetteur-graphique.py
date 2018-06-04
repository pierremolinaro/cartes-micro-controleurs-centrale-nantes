#! /usr/bin/env python
# -*- coding: UTF-8 -*-

# Tkinter: voir http://apprendre-python.com/page-tkinter-interface-graphique-python-tutoriel
#——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————*

import socket, numpy, time, Tkinter as tk
global so

#——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————*

def envoi ():
  #--- Construire les données
  donnees = numpy.array ([1, 2, 3, 4], dtype=numpy.uint8)
  #--- Envoyer les données
  print ("  Envoi de " + str (donnees.size) + " octets...")
  so.sendall (donnees)

#——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————*

#--- Caractéristiques du serveur
serveurTCP = "192.168.0.14"
port = 16009
#--- Établir la connexion
so = socket.socket (socket.AF_INET, socket.SOCK_STREAM)
so.connect ((serveurTCP, port))
print ("  Connexion sur {}:{}".format (serveurTCP, port))
#--- Création de la fenêtre
fenetre = tk.Tk()
#--- Bouton pour envoyer un octet
bouton = tk.Button (fenetre, text="Envoyer", command=envoi)
bouton.pack()
#--- Bouton pour quitter
bouton = tk.Button (fenetre, text="Quitter", command=fenetre.quit)
bouton.pack()
#--- Boucle des gestion des évènements
fenetre.mainloop ()
#--- Fermer la connexion
print ("  Fermeture")
so.shutdown (socket.SHUT_RDWR)
so.close ()

#----------------------------------------------------------------------------------------------------------------------*
