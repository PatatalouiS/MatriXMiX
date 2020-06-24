<div align='center'>
	<img src='http://storage.patatalouis.fr/logo.png'/>
</div>

<h1> Introduction </h1>

This project is a tool for manipulating and calculating matrices in <img src="https://latex.codecogs.com/gif.latex?\mathbb{R}"/> 
and <img src="https://latex.codecogs.com/gif.latex?\mathbb{C}"/> sets. It will allow you to perform basic matrix operations as well as certain decomposition and diagonalization operations. The tool is currently geared towards teaching and allows students to easily correct their algebra exercices, wich are often difficult to correct on their own. All this with a beautiful <img src="https://latex.codecogs.com/gif.latex?\LaTeX"/> typesetting.  For developpers, the library we created for matrix calculations can be reused as a static or shared library in your own programs.

<h4>⚠️ Please read the installation and build instructions carefully ️⚠️ </h4>
<h4>⚠️ All the bash commands described here are executed from the root of the project ️⚠️ </h4>

<h1> Install </h1>
 
Statically executables are available to avoid having to compile teh sources yourself. However, some consitions must be met to be able to execute them without error. If you do not have the 	requisite conditions please read the Build section. For the moment the application is not available on Windows but we wiil do the necesseray to hava a complete cross-compilation later.

your OS must be :
<ul>
	<li><b>Debian based distribution with GLIBC version >= 2.27</b> <i>( i.e from Ubuntu 18.04 LTS )</i></li>
	<li><b>Mac OSX 10.14 or higher</b></li>
</ul>

You just have to download the good executable in the <code><b><a href='https://forge.univ-lyon1.fr/p1710179/MatriXMiX/-/releases'>Releases</a></b></code> section and :

<b>UNIX</b>

Make sure the AppImage is executable with :
<pre>$ chmod a+x MatriXMiX-x86_64.AppImage </pre>
and after :
<pre>$ ./MatriXMiX-x86_64.AppImage </pre>

After, only if you want, you can put the executable in your Desktop entries with the <a href='https://github.com/TheAssassin/AppImageLauncher'> AppImageLauncher tool </a>.

<b>OSX</b>

Just double click on the .dmg ! <i> (And drag it to your Applictions folder if you like MatriXMiX) </i>

<h1>Build</h1>

<b> OSX and Unix </b>

Before compiling, you need to install the only dependencies of the project : The <b>Qt</b> Framework. Please note, sometimes its installation can be a bit tedious. We advise you to install <b>Qt</b> OpenSource via their graphic installer available on the <a href='https://www.qt.io/download-open-source?hsCtaTracking=9f6a2170-a938-42df-a8e2-a9f0b1d6cdce%7C6cb0de4f-9bb5-4778-ab02-bfb62735f3e5'>Official Website</a>. Preferably, choose in the utility ti install version <b>12.8</b> of <b>Qt</b> because <b>MatriXMiX</b> has been developed on it its entirely.

After, make sure the qmake tool is availble in your PATH env variable by :
<pre>$ export PATH=~/Qt/5.12.8/gcc_64/bin:$PATH                 <i> // Unix systems </i></pre>
<pre>$ export PATH=~/Qt/5.12.8/clang_64/bin:$PATH               <i> // OSX systems </i></pre>

finally, you can do : 
<pre>$ make </pre>
Which will generate the following executables in <code><b>./bin</b></code> folder :
<ul>
	<li><b>MatriXMiX</b> : the MatriXMiX app in graphic version</li>
	<li><b>MatriXMiX_TXT</b> : A TXT Version of MatriXMiX </li>
	<li><b>MatriXMiX_Test</b> : regression tests for MatriXMiX </li>
	<li><b>libMatriXMiX.a</b> : a static lib of our Matrix Module for your <code><b>C++</code></b> programs </li>
</ul>

And execute MatriXMiX with :
<pre>$ ./bin/MatriXMiX              <i>// Unix systems</i> </pre>
<pre>$ open ./bin/MatriXMiX         <i>// OSX systems</i> </pre>

<h4> Other Makefile rules </h4>
<ul>
	<li><b>make clean</b> : clean .obj files, all the stuff to make the finla binaries</li>
	<li><b>make veryclean</b> : clean all </li>
	<li><b>make documentation</b> : generates the <code><b>Doxygen</b></code> documentation</li>
</ul>

<h1> Documentation </h1>

As explaned before, you can generate full documentation with the command :
<pre>$ make documentation </pre>

Be ensure you have the required <code><b>Doxygen</b></code> tool for this. if not, you can install it with :
<pre>$ sudo apt install doxygen        <i> // Unix systems </i></pre>
<pre>$ brew install doxygen            <i> // OSX systems </i></pre>

<h1> Use MatriXMiX </h1>

Using MatriXMiX is very simple, you have just to put some matrices in the Library an after, make calculations on these matrices in the main menu.
If you don't see your matrix for a calculation, it's because your matrix is not mathematically compatible with this operation.

You can save your current library with the File menu. a .mtmx txt file is created.
Also, you can load a .mtmx file to restore a previous library.

<h1> Third Party Libraries </h1>

The MatriXMiX app uses :
<ul>
	<li><b><a href='https://gitlab.com/libeigen/eigen'>Eigen</a></b> : A C++ template library for linear algebra</li>
	<li><b><a href='https://github.com/jkriege2/JKQtPlotter'>JQKTPlotter</a></b> : For <img src="https://latex.codecogs.com/gif.latex?\LaTeX"/> typesetting</li>
	<li><b><a href='https://beltoforion.de/article.php?a=muparserx'>MuParserX</a></b> : for parse the user inputs easily</li>
</ul>

<h1> Contact </h1>

If you have any problems for runing, building, or using MatriXMiX please contact us : <br>
<a href="mailto:maxime.olivie@etu.univ-lyon1.fr">Support 1</a> <br>
<a href="mailto:tarik.boumaza@etu.univ-lyon1.fr">Support 2</a>

<h1> Authors </h1>

<ul>
	<li>p1712754 CERBULEAN Ana-Maria</li>
	<li>p1710179 OLIVIE Maxime</li>
	<li>p1716451 SEBIA Hana</li>
	<li>p1712760 BOUMAZA Tarik</li>
</ul>
<br>
