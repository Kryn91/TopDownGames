# ==========================
#   Projet SFML Makefile
# ==========================

# 🔧 Compilateur et options
CXX      := g++
CXXFLAGS := -Wall -std=c++17 -Iinclude

# 🔗 Librairies SFML
LDFLAGS  := -lsfml-graphics -lsfml-window -lsfml-system

# 🗂️ Répertoires
SRC_DIR  := src
OBJ_DIR  := obj
BIN_DIR  := bin

# 🎯 Nom de l'exécutable
TARGET   := $(BIN_DIR)/program

# 📦 Recherche automatique de tous les .cpp
SRC := $(shell find $(SRC_DIR) -name "*.cpp")
OBJ := $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# ==========================
#   Règles principales
# ==========================

# 🧱 Règle par défaut
all: $(TARGET)

# 🔨 Liaison finale
$(TARGET): $(OBJ)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJ) -o $@ $(LDFLAGS)
	@echo "✅ Build terminé : $(TARGET)"

# 🧩 Compilation des .cpp → .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo "🧩 Compilation : $<"

# 🧹 Nettoyage
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
	@echo "🧹 Nettoyage terminé"

# 🚀 Exécution rapide
run: all
	./$(TARGET)

# ==========================
#   Fin du Makefile
# ==========================
