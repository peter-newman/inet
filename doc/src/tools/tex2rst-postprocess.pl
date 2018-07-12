s/^::$//g;
s/^.. raw:: latex$//g;

s/   ###ned###/.. code-block:: ned\n/g;
s/   ###note###/.. note::\n/g;

s/:ttt:§(.*?)§/``$1``/g;
s/:cppclass:§(.*?)§/:cppclass:`$1`/g;
s/:ffunc:§(.*?)§/:ffunc:`$1`/g;
s/:fvar:§(.*?)§/:fvar:`$1`/g;
s/:protocol:§(.*?)§/:protocol:`$1`/g;
s/:nedtype:§(.*?)§/:nedtype:`$1`/g;

s|\s*\\cppsnippet\{(.*?)\}\{(.*?)\}|.. literalinclude:: lib/Snippets.cc\n   :language: cpp\n   :start-after: !$1\n   :end-before: !End\n   :name: $2|g;
s|\s*\\msgsnippet\{(.*?)\}\{(.*?)\}|.. literalinclude:: lib/Snippets.msg\n   :language: msg\n   :start-after: !$1\n   :end-before: !End\n   :name: $2|g;
