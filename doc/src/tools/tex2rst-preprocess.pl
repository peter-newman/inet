s/\\begin\{verbatim\}/\\begin{verbatim}###verbatim###/g;
s/\\end\{verbatim\}/\\end{verbatim}/g;

s/\\begin\{ned\}/\\begin{verbatim}###ned###/g;
s/\\end\{ned\}/\\end{verbatim}/g;

s/\\begin\{inifile\}/\\begin{verbatim}###inifile###/g;
s/\\end\{inifile\}/\\end{verbatim}/g;

s/\\begin\{XML\}/\\begin{verbatim}###XML###/g;
s/\\end\{XML\}/\\end{verbatim}/g;

s/\\begin\{note\}/\\begin{verbatim}###note###/g;
s/\\end\{note\}/\\end{verbatim}/g;

s/\\begin\{important\}/\\begin{verbatim}###important###/g;
s/\\end\{important\}/\\end{verbatim}/g;

s/\\begin\{warning\}/\\begin{verbatim}###warning###/g;
s/\\end\{warning\}/\\end{verbatim}/g;

s/\\begin\{caution\}/\\begin{verbatim}###caution###/g;
s/\\end\{caution\}/\\end{verbatim}/g;

s/\\ttt\{(.+?)\}/:ttt:§$1§/g;
s/\\cppclass\{(.+?)\}/:cppclass:§$1§/g;
s/\\ffunc\{(.+?)\}/:ffunc:§$1§/g;
s/\\ffilename\{(.+?)\}/:ffilename:§$1§/g;
s/\\fvar\{(.+?)\}/:fvar:§$1§/g;
s/\\fpar\{(.+?)\}/:fpar:§$1§/g;
s/\\fgate\{(.+?)\}/:fgate:§$1§/g;
s/\\protocol\{(.+?)\}/:protocol:§$1§/g;
s/\\nedtype\{(.+?)\}/:nedtype:§$1§/g;
s/\\msgtype\{(.+?)\}/:msgtype:§$1§/g;
