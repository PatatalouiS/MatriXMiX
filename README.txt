********************************************************************************
********************************************************************************
  **                                                                        **  
  **                           README MATRIXMIX                             **
  **                                                                        **  
********************************************************************************
********************************************************************************

******** DEVELOPPEURS *******

p1712754 CERBULEAN Ana-Maria
p1710179 OLIVIE Maxime	
p1716451 SEBIA Hana
p1712760 BOUMAZA Tarik

  
********************************************************************************
********************************************************************************

/!\ TOUTES LES COMMANDES DE CE README SE LANCENT DEPUIS LA RACINE DU MODULE ( Ce répertoire ) /!\

/!\ LA COMPILATION DE L'APPLICATION EN MODE GRAPHIQUE REQUIERT L'INSTALLATION DE QT /!\
	(Vous pouvez l'installer via apt-get (Linux) ou brew (OSX)) 

/!\ Pour une documentation plus complète, veuillez consulter le fichier 'doc/html/index.html' /!\

________________________________________________________________________________


******** DESCRIPTION DE L'APPLICATION ********

	MatriXMiX est un projet réalisé dans le cadre de l’UE LIFAP4 (Printemps 2019).
	Cette application a pour but de réaliser des calculs matriciels basiques : addition, soustraction, multiplication, division, échelonnage...
Elle possède également des fonctionnalités plus poussées telles que l'étude des dimensions, l'étude des valeurs et vecteurs propres, et la diagonalisation.
	Sont fournis trois exécutables: 
			MatriXMiX (version graphique)
			MatriXMiX_txt (version texte)
			MatriXMiX_test (exécute des tests de non régression)	
	L'application peut être utilisée par des étudiants ou des enseignants pour résoudre des exercices basiques.
	Le module Matrix (accompagné du module Gauss, Fraction et Polynomial) peut quant à lui être réutilisé par d'autres développeurs ayant recourt à des calculs matriciels poussés.


******** ARBORESCENCE GÉNÉRALE ******** :

	P1712754_P1710179_P1716451_P1712760/
		
		Makefile
		
		README.txt

		src/
							
			maths/
				Matrix.h
				Matrix.cpp
				MatrixLibrary.h
				MatrixLibrary.cpp
				Gauss.h
				Gauss.cpp
				Fraction.h
				Fraction.cpp
				Polynomial.h
				Polynomial.cpp
				VectorX.h
				VectorX.cpp
			txt/
				MatriXMiXTXT.h
				MatriXMiXTXT.cpp
				mainTxt.cpp
				mainTest.cpp	
			qt/
				main.cpp
				AbstractOperationWidget.h
				AbstractOperationWidget.cpp
				BinaryOpMatrixMatrixWidget.h
				BinaryOpMatrixMatrixWidget.cpp
				BinaryOpMatrixNumberWidget.h
				BinaryOpMatrixNumberWidget.cpp
				DiagonalisationWidget.h
				DiagonalisationWidget.cpp
				Error.h
				Error.cpp
				ExprEvalWidget.h
				ExprEvalWidget.cpp
				HelpWindow.h
				HelpWindow.cpp
				HelpWindowQt.h
				HelpWindowQt.cpp
				LibraryWindow.h	
				LibraryWindow.cpp
				MainWindow.h
				MainWindow.cpp
				MatrixViewWidget.h
				MatrixViewWidget.cpp
				MenuBar.h
				MenuBar.cpp
				SetMatrixWidget.h
				SetMatrixWidget.cpp	
				ShowMatrixWidget.h
				ShowMatrixWidget.cpp
				UnaryOpWidget.h
				UnaryOpWidget.cpp
		
		ext/
			Eigen/
			latex/

		obj/

		bin/

		data/
			icons/
				MatriXMiX.icns
				MatriXMiX.png
			start/
				MatrixSet.mtmx
			background.png
			create.png
			data.qrc
			library.png
			logo.png
			minus.png
			plus.png
			qt.png
			quit.png
			save.png
			trash.png

		documentation.h		

		doc/
				

	

________________________________________________________________________________


******** COMPILATION / MAKEFILE ********


Note : La Compilation est CROSS-OS, vous pouvez compiler autant sur un systeme
		LINUX que sur un système OSX.


	Compilation du projet : 
		-> Commande "make" depuis ce répertoire courant génèrera les cibles suivantes :
			bin/MatriXMiX
			bin/MatriXMiX_TXT
			bin/MatriXMiX_Test

	Autres Cibles du Makefile :	
	-> Commande "make clean" supprimera les exécutables dans bin/ , les fichiers objets dans obj/, les fichiers resources dans resources/ et les fichiers moc dans moc/
	-> Commande "make veryclean" supprimera TOUS fichiers générés par la commande "make"		
	-> Commande "make documentation" génerera la documentation du module.


________________________________________________________________________________

******** LIBRAIRIES EXTERNES ********
 
L'application MatriXMiX requiert l'utilisation de deux librairies externes: 
	- eigen 3.3.7 : pour réaliser des calculs poussés de diagonalisation
	- latex : pour un affichage plus conventionnel des résultats mathématiques


________________________________________________________________________________

******** EXECUTION ET DESCRIPTION ********

	"./bin/MatriXMiX" -> Execute MatriXMiX en version graphique
	"./bin/MatriXMiX_TXT" -> Execute MatriXMiX en version texte 
	"./bin/MatriXMiX_Test" -> Execute l'ensemble des tests de non régression de MatriXMiX en version texte

Après l'ajout de matrices dans l'application, celle-ci propose les fonctionnalités suivantes:

*** Opérations binaires ***
Addition
Soustraction
Multiplication par un scalaire
Multiplication matricielle
Division
Puissance

*** Opérations unaires ***
Determinant
Trace
Inverse
Echelonnage
Etude des dimensions

*** Diagonalisation ***
Polynôme caractéristique
Valeurs/Vecteurs
Diagonalisation
Evaluation d'expression


******* MatriXMiX version graphique *******
- Sauvegarde de la librairie de matrices dans un fichier au format ".mtmx"
- Lecture de matrices à partir d'un fichier ".mtmx"


**** NB ****
Un jeu de matrices est fourni dans le répertoire data/start/MatrixSet.mtmx
Vous pouvez l'ouvrir depuis l'onglet fichier->ouvrir de l'application

________________________________________________________________________________


******** DOCUMENTATION ********

	-> Afin de fournir de la documentation pour ce programme, nous utilisons l’outil Doxygen. 
	Le fichier de configuration (doxyfile) se trouve dans le répertoire doc/image.doxy 
	La documentation est automatiquement générée grâce à la commande :

	"doxygen doc/image.doxy" ( nécessite l'installation de Doxygen Via apt-get, brew ...)

	-> La documentation peut être générée aussi via une cible du Makefile : "make documentation"

________________________________________________________________________________


********** NOTE AUX DEVELOPPEURS **********

Pour Linux, il faudra installer (sudo apt install g++ doxygen apt-get install qtcreator qt5-default)
- g++ (sudo apt install g++)
- doxygen (sudo apt install doxygen)
- qmake (sudo apt-get install qmake qt5-default OU brew install qt) pour le mode graphique sous





