# pg_postal_code_ca
an efficient, validated, formatted Canadian postal code type

<h3>Description</h3>
This type supports efficient, validated, formatted usage of Canadian postal codes. It provides sane ordering functionality through implementation of custom comparison operators.

<h3>Installation</h3>
<pre>
curl -s -S -L https://github.com/rlichtenwalter/pg_postal_code_ca/archive/master.zip > pg_postal_code_CA.zip
unzip pg_postal_code_ca.zip
(cd pg_postal_code_ca-master &amp;&amp; make PG_CONFIG=&lt;optional custom pg_config path&gt;)
(cd pg_postal_code_ca-master &amp;&amp; make PG_CONFIG=&lt;optional custom pg_config path&gt; install)
(cd ~postgres &amp;&amp; sudo -u postgres psql -c 'CREATE EXTENSION pg_postal_code_ca;')
</pre>

<h3>Usage</h3>
<pre>
testuser=# SELECT 'h2e3f1'::canadian_postal_code;
 canadian_postal_code
----------------------
 H2E 3F1
(1 row)

testuser=# SELECT 'H2E 3F1'::canadian_postal_code;
 canadian_postal_code
\----------------------
 H2E 3F1
(1 row)

testuser=# SELECT 'A2CCF3'::canadian_postal_code;
ERROR:  invalid input format for candian_postal_code: 'A2CCF3'
LINE 1: SELECT 'A2CCF3'::canadian_postal_code;
</pre>
