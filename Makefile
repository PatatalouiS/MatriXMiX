#  __  __       _        ___  ____  __ ___  __
# |  \/  | __ _| |_ _ __(_) \/ /  \/  (_) \/ /
# | |\/| |/ _` | __| '__| |\  /| |\/| | |\  /
# | |  | | (_| | |_| |  | |/  \| |  | | |/  \
# |_|  |_|\__,_|\__|_|  |_/_/\_\_|  |_|_/_/\_\

# Copyright (C) 2019-2020, Sebia Hana, Cerbulean Ana-Maria, Boumaza Tarik, Olivié Maxime.

# This file is part of MatriXMiX.

# MatriXMiX is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# MatriXMiX is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with MatriXMiX.  If not, see <https://www.gnu.org/licenses/>

BIN_DIR = bin
OBJ_DIR = obj
SRC_DIR = src
MOC_DIR = moc
RESOURCES_DIR = resources
DOC_DIR = doc

CC = g++
LD = g++

CC_FLAGS = -g -std=c++11 -Wall -Wextra -c -fPIC -O3
LD_FLAGS = -g -std=c++11 -Wall -Wextra -fPIC -O3

CLEAN_FLAGS = -v -r -f

EIGEN = -I ext/Eigen


all : makedir TXT Qt Test Lib

makedir :
	@mkdir -p bin obj resources moc

Qt : MatriXMiX.make
	make -f MatriXMiX.make

TXT : makedir bin/MatriXMiX_TXT

Test : makedir bin/MatriXMiX_Test

Lib : makedir bin/libmatrix.a

bin/libmatrix.a : obj/Matrix.o obj/MatrixLibrary.o obj/Polynomial.o obj/Fraction.o obj/MatriXMiXTXT.o obj/Gauss.o obj/Utils.o
	ar rcs $@ $^


MatriXMiX.make : MatriXMiX.pro
	qmake -makefile -o $@ $<

bin/MatriXMiX_TXT : obj/mainTXT.o obj/Matrix.o obj/MatrixLibrary.o obj/Polynomial.o obj/Fraction.o obj/MatriXMiXTXT.o obj/VectorX.o obj/Gauss.o obj/Utils.o
	$(LD) $^ -o $@

obj/MatriXMiXTXT.o : src/txt/MatriXMiXTXT.cpp src/txt/MatriXMiXTXT.h src/maths/MatrixLibrary.h
	$(CC) $(CC_FLAGS) $< -o $@ $(EIGEN)

obj/mainTXT.o : src/txt/mainTXT.cpp src/maths/MatrixLibrary.h
	$(CC) $(CC_FLAGS) $< -o $@ $(EIGEN)



bin/MatriXMiX_Test : obj/mainTest.o obj/Matrix.o obj/MatrixLibrary.o obj/Polynomial.o obj/Fraction.o obj/VectorX.o obj/Gauss.o obj/Utils.o
	$(LD) $^ -o $@

obj/mainTest.o : src/txt/mainTest.cpp src/maths/Fraction.h src/maths/MatrixLibrary.h
	$(CC) $(CC_FLAGS) $< -o $@ $(EIGEN)



obj/Matrix.o : src/maths/Matrix.cpp src/maths/VectorX.h src/maths/Polynomial.h
	$(CC) $(CC_FLAGS) $< -o $@ $(EIGEN)

obj/MatrixLibrary.o : src/maths/MatrixLibrary.cpp src/maths/MatrixLibrary.h src/maths/Matrix.h
	$(CC) $(CC_FLAGS) $< -o $@ $(EIGEN)

obj/Polynomial.o : src/maths/Polynomial.cpp src/maths/Polynomial.h src/maths/VectorX.h
	$(CC) $(CC_FLAGS) $< -o $@

obj/Fraction.o : src/maths/Fraction.cpp src/maths/Fraction.h
	$(CC) $(CC_FLAGS) $< -o $@

obj/VectorX.o : src/maths/VectorX.cpp src/maths/VectorX.h
	$(CC) $(CC_FLAGS) $< -o $@

obj/Gauss.o : src/maths/Gauss.cpp src/maths/Gauss.h src/maths/Matrix.h
	$(CC) $(CC_FLAGS) $< -o $@ $(EIGEN)

obj/Utils.o : src/maths/Utils.cpp src/maths/Utils.hpp src/maths/Fraction.h
	$(CC) $(CC_FLAGS) $< -o $@ $(EIGEN)


clean :
	rm $(CLEAN_FLAGS) $(MOC_DIR)/* $(OBJ_DIR)/* $(RESOURCES_DIR)/* .qmake.stash*


veryclean : clean
	rm $(CLEAN_FLAGS) $(BIN_DIR)/* $(DOC_DIR)/html MatriXMiX.make MatriXMiX.pro.*


documentation :
	doxygen doc/MatriXMiX.doxy
