s/^::$//g;
s/^.. raw:: latex$//g;

s/   ###verbatim###/::\n/g;
s/   ###XML###/.. code-block:: xml\n/g;
s/   ###ned###/.. code-block:: ned\n/g;
s/   ###inifile###/.. code-block:: ini\n/g;
s/   ###note###/.. note::\n/g;
s/   ###important###/.. important::\n/g;
s/   ###warning###/.. warning::\n/g;
s/   ###caution###/.. caution::\n/g;

s/:ttt:§(.*?)§/``$1``/g;
s/:cppclass:§(.*?)§/:cppclass:`$1`/g;
s/:ffilename:§(.*?)§/:ffilename:`$1`/g;
s/:ffunc:§(.*?)§/:ffunc:`$1`/g;
s/:fvar:§(.*?)§/:fvar:`$1`/g;
s/:fpar:§(.*?)§/:fpar:`$1`/g;
s/:fgate:§(.*?)§/:fgate:`$1`/g;
s/:protocol:§(.*?)§/:protocol:`$1`/g;
s/:nedtype:§(.*?)§/:nedtype:`$1`/g;
s/:msgtype:§(.*?)§/:msgtype:`$1`/g;

s|\s*\\cppsnippet\{(.*?)\}\{(.*?)\}|.. literalinclude:: lib/Snippets.cc\n   :language: cpp\n   :start-after: !$1\n   :end-before: !End\n   :name: $2|g;
s|\s*\\msgsnippet\{(.*?)\}\{(.*?)\}|.. literalinclude:: lib/Snippets.msg\n   :language: msg\n   :start-after: !$1\n   :end-before: !End\n   :name: $2|g;
s|\s*\\nedsnippet\{(.*?)\}\{(.*?)\}|.. literalinclude:: lib/Snippets.ned\n   :language: ned\n   :start-after: !$1\n   :end-before: !End\n   :name: $2|g;
s|\s*\\inisnippet\{(.*?)\}\{(.*?)\}|.. literalinclude:: lib/Snippets.ini\n   :language: ini\n   :start-after: !$1\n   :end-before: !End\n   :name: $2|g;
s|\s*\\xmlsnippet\{(.*?)\}\{(.*?)\}|.. literalinclude:: lib/Snippets.xml\n   :language: xml\n   :start-after: !$1\n   :end-before: !End\n   :name: $2|g;
