#include <opencv2/opencv.hpp> 
int main() { 
    // Création d'un objet capture pour accéder à la caméra 
    cv::VideoCapture cap(0); 
    // Vérification si la capture de la caméra est réussie 
    if (!cap.isOpened()) { 
        std::cerr << "Erreur: Impossible d'ouvrir la caméra" << std::endl; 
        return -1; 
    } 
    // Création d'une fenêtre 
    cv::namedWindow("Camera", cv::WINDOW_NORMAL); 
    // Boucle infinie pour afficher le flux de la caméra 
    while (true) { 
        // Lecture d'une nouvelle image de la caméra 
        cv::Mat frame; 
        cap >> frame; 
        // Vérification si l'image est vide 
        if (frame.empty()) { 
            std::cerr << "Erreur: Image vide" << std::endl; 
            break; 
        } 
        // Affichage de l'image dans la fenêtre 
        cv::imshow("Camera", frame); 
        // Attendre 30ms et vérifier si l'utilisateur a appuyé sur la touche 'q' pour quitter 
        if (cv::waitKey(30) == 'q') { 
            break; 
        } 
    } 
    // Libération des ressources 
    cap.release(); 
    cv::destroyAllWindows(); 
    return 0; 
}