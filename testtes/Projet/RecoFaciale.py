[16:08] Emrys DEROUICHE
import cv2 

import face_recognition 

import serial 

import time 

# Initialiser la webcam USB (par exemple, index 1) 

cap = cv2.VideoCapture(0) 

# Initialisation du port série 

try: 

    ser = serial.Serial( 

        port='/dev/ttyACM0',  # Remplacez par le port série correct, par exemple 'COM3' sur Windows ou '/dev/ttyUSB0' sur Linux 

        baudrate=9600,        # Débit en bauds 

        parity=serial.PARITY_NONE, 

        stopbits=serial.STOPBITS_ONE, 

        bytesize=serial.EIGHTBITS, 

        timeout=1 

    ) 

except serial.SerialException as e: 

    print(f"Erreur: Impossible d'ouvrir le port série: {e}") 

    exit() 

time.sleep(2) 

# Charger et encoder l'image de référence 

reference_image = face_recognition.load_image_file("./Photo_Emrys_Derouiche.jpeg") 

reference_encoding = face_recognition.face_encodings(reference_image)[0] 

font = cv2.FONT_HERSHEY_SIMPLEX 

while True: 

    # Lire notre frame (image) 

    ret, image = cap.read() 

    if not ret: 

        print("Erreur de lecture de l'image de la webcam.") 

        break 

    # Convertir l'image de la webcam de BGR à RGB 

    image_rgb = cv2.cvtColor(image, cv2.COLOR_BGR2RGB) 

    # Trouver toutes les faces et leurs encodages dans l'image actuelle de la webcam 

    face_locations = face_recognition.face_locations(image_rgb) 

    face_encodings = face_recognition.face_encodings(image_rgb, face_locations) 

    # Comparer chaque visage trouvé avec le visage de référence 

    for (top, right, bottom, left), face_encoding in zip(face_locations, face_encodings): 

        matches = face_recognition.compare_faces([reference_encoding], face_encoding) 

        if matches[0]: 

            name = "Visage reconnu" 

            if ser.isOpen(): 

                try: 

                    ser.write(b'R') 

                    time.sleep(1) 

                except serial.SerialException as e: 

                    print(f"Erreur d'écriture sur le port série: {e}") 

        else: 

            name = "Inconnu" 

            if ser.isOpen(): 

                try: 

                    ser.write(b'r') 

                    time.sleep(1) 

                except serial.SerialException as e: 

                    print(f"Erreur d'écriture sur le port série: {e}") 

        # Dessiner un rectangle autour du visage 

        cv2.rectangle(image, (left, top), (right, bottom), (255, 0, 0), 2) 

        # Ajouter une étiquette avec le nom en dessous du visage 

        cv2.putText(image, name, (left, bottom + 20), font, 0.75, (255, 0, 0), 2) 

    # Afficher le rendu de la webcam 

    cv2.imshow("image", image) 

    # Appuyez sur 'q' pour quitter 

    if cv2.waitKey(1) == ord("q"): 

        break 

# Détruire toutes les fenêtres après avoir quitté le programme 

cap.release() 

cv2.destroyAllWindows() 

# Fermer le port série 

ser.close() 
