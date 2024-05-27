# Définition des variables
CC = gcc
CFLAGS = -Wall -g
LIBS = -lGL -lGLU -lglut -lX11

# Nom de l'exécutable
TARGET = main

# Liste des fichiers objets
OBJS = main.o GfxLib.o

# Règle par défaut
all: $(TARGET)

# Règle pour créer l'exécutable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) $(LIBS)

# Règle pour créer les fichiers objets
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Règle de nettoyage
clean:
	rm -f *~ *.o $(TARGET)
