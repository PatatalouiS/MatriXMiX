/** \mainpage MatriXMiX

\author 
	CERBULEAN Ana-Maria p1712754 \n
	OLIVIE Maxime p1710179 \n
	SEBIA Hana p1716451 \n
	BOUMAZA Tarik p1712760 \n

\version 1.0

\date 06 Mai 2019

\section Introduction
		MatrixMiX est une application réalisée dans le cadre de l’UE LIFAP4 au cours du printemps 2019.\n 
		Cette application permet de réaliser différents calculs matriciels basiques ainsi que des opérations liées à la diagonalisation.\n
		Afin de réaliser cette application, nous avons utilisé le gestionnaire de versions Git, le générateur de documentation Doxygen,
	ainsi que Qt pour la réalisation de l'application en mode graphique. \n
		Le code est écrit en C++.\n

	<H3><B>ATTENTION</B></H3>Toutes les commandes doivent être exécutées depuis le répertoire courant de l'application ! 

\n
\section Compilation
		<B>Note1</B> : La compilation est CROSS-OS, vous pouvez compiler autant sur un système <B>LINUX</B> que sur un système <B>OSX</B>, à condition d'avoir installé <B>g++</B>\n
		<B>Note2</B> : L'installation de <B>qmake</B> est nécessaire pour la compilation du mode graphique de ce projet, vous pouvez l'installer via :

			$ sudo apt-get install qmake    // Pour les systèmes Linux
			$ brew install qt               // Pour les systèmes OSX (après avoir installé 'brew')

	Pour compiler tout le projet, éxecuter la commande :
 
		$ make

	depuis le répertoire courant pour génerer toutes les cibles : \n
	<B>bin/MatriXMiX_Test\n
	bin/MatriXMiX_TXT\n
	bin/MatriXMiX\n</B>
 
	Pour générer l'exécutable <B>MatriXMiX_Test</B> seulement :

		$ make Test

	Pour générer l'exécutable <B>MatriXMiX_TXT</B> seulement:

		$ make TXT

	Pour générer l'exécutable <B>MatriXMiX</B>  seulement:

		$ make Qt
 
	Pour supprimer <B>TOUS</B> les exécutables dans <B>bin/</B>, les fichiers objets dans <B>obj/</B>, les fichiers moc dans <B>moc/</B> et les fichiers resources dans <B>resources/</B>  
 
		$ make clean

	Pour supprimer <B>TOUS</B> les fichiers générés par la commande 'make'
 
		$ make veryclean 
		 
	Egalement, vous pouvez générer la documentation avec <B>Doxygen</B> Via :

		$ make docs

\n
\section Exécution
	<B>Commandes d'Execution :</B>

	Pour exécuter <B>MatriXMiX_Test</B> :

		$ ./bin/MatriXMiX_Test       // Sous Linux
		$ open bin/MatriXMiX_Test    // Sous OSX

	Pour exécuter <B>MatriXMiX_TXT</B> :

		$ ./bin/MatriXMiX_TXT      	 // Sous Linux
		$ open bin/MatriXMiX_TXT     // Sous OSX

	Pour exécuter <B>MatriXMiX</B> :

		$ ./bin/MatriXMiX        	// Sous Linux
		$ open bin/MatriXMiX.app    // Sous OSX

	<B>Description des exécutables</B> :

	<B>MatriXMiX_Test</B> : Exécutable d'une série de tests de non régression des différents modules présents dans src/maths/

	<B>MatriXMiX_TXT</B> : Exécutable de l'application en mode texte.
	 
	<B>MatriXMiX</B> : Exécutable de l'application en mode graphique sur Linux.

	<B>MatriXMiX.app</B> : Exécutable de l'application en mode graphique sur OSX.
	 
\n
\section Documentation
	Afin de fournir de la documentation pour ce programme, nous utilisons l’outil <B>Doxygen</B>.\n
	Le fichier de configuration <B>Doxygen</B> se trouve dans le répertoire <B>doc/image.doxy</B>\n
	La documentation est automatiquement générée grâce à la commande :
	 
		$ doxygen doc/doxyfile
	 
	Ou bien comme mentionné plus haut :

		$ make docs

	Egalement vous pouvez télécharger l'outil <B>doxygen</B> via les commandes :

		$ sudo apt-get install doxygen    // Sur systèmes LINUX
		$ brew install doxygen           // Sur systèmes OSX


*/





