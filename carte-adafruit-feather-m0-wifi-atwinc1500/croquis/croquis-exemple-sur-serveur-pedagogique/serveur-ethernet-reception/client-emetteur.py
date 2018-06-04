#! /usr/bin/env python
# -*- coding: UTF-8 -*-

#——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————*

import socket, numpy

#——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————*

#--- Caractéristiques du serveur
serveurTCP = "192.168.0.14"
port = 16009
#--- Établir la connexion
so = socket.socket (socket.AF_INET, socket.SOCK_STREAM)
so.connect ((serveurTCP, port))
print ("  Connexion sur {}:{}".format (serveurTCP, port))
#--- Construire les données
donnees = numpy.array ([1, 2, 3, 4], dtype=numpy.uint8)
#--- Envoyer les données
print ("  Envoi de " + str (donnees.size) + " octets...")
so.sendall (donnees)
#--- Fermer la connexion
print ("  Fermeture")
so.shutdown (socket.SHUT_RDWR)
so.close ()

#----------------------------------------------------------------------------------------------------------------------*
