# squeaker
Copyright Metaspex - 2022
mailto:info@metaspex.com

This repository contains the complete ontology for a social network called "Squeaker". It exercises a good number of Metaspex
abstractions for data modeling. Consult the diagram for a description of relationships between the ontology types.
Dotted lines represent links (kind of URLs), solid lines represent ownerships (origin and target end up in the same document
in the database). Arrows starting with a circled plus sign denote composite (one to many) relationships.

The code enters directly a C++ compiler such as gcc-12. No preprocessing is involved. The same ontology can be reused across
various offline or online solutions. When an online solution is produced, the C++ compiler produces a binary module either for
Apache or Nginx, depending on compilation options.

Although it looks simple, the ontology carries with it a number of behaviors that do not require additional coding. In particular,
if a post is removed, the corresponding likes, replies and reposts disappear automatically.
This is thanks to the high-level "link" construct, which enforces automatically referential integrity maintenance. Without
running any form of SQL.

No mention is made of a database. The mapping from logical names and physical databases is made entirely in the configuration
file. It is therefore possible to deploy the same binary on various databases for persistence (Couchbase, MongoDB, CouchDB).

A post update service is added as an example. It exposes an HTTP REST JSON in/JSON out service.

With indexes and using Metaspex's high-level cursors or link inversion capabilities, it is possible to find all posts a user
has made, all replies on a given post, etc.

Creating a post consumes mere microseconds in the application tier, making it capable to process thousands of posts per second
on a handful of Raspberry Pi/ARM Cortex processors!
