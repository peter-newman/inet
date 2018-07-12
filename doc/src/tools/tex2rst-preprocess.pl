s/\\begin\{ned\}/\\begin{verbatim}###ned###/g;
s/\\end\{ned\}/\\end{verbatim}/g;

s/\\begin\{note\}/\\begin{verbatim}###note###/g;
s/\\end\{note\}/\\end{verbatim}/g;

s/\\ttt\{(.+?)\}/:ttt:§$1§/g;
s/\\cppclass\{(.+?)\}/:cppclass:§$1§/g;
s/\\ffunc\{(.+?)\}/:ffunc:§$1§/g;
s/\\fvar\{(.+?)\}/:fvar:§$1§/g;
s/\\protocol\{(.+?)\}/:protocol:§$1§/g;
s/\\nedtype\{(.+?)\}/:nedtype:§$1§/g;
