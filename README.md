# Paging and RAM replacment algorithms

This program simulated how the OS deals with replacing the pages in the RAM to be as optimal as possible.

# Algorithms

We have 4 Paging and Replacement algorithms:

- optimal
- FIFO
- LRU
- clock

# Optimal

In this algorithm, OS replaces the page that will not be used for the longest
period of time in future.
The idea is simple, for every reference we do following :

- If referred page is already present, increment hit count.
- If not present, find if a page that is never referenced in future. If such a page exists,
  replace this page with new page. If no such page exists, find a page that is
  referenced farthest in future. Replace this page with new page.

# FIFO

This is the simplest page replacement algorithm. In this algorithm, the operating
system keeps track of all pages in the memory in a queue, the oldest page is in the
front of the queue. When a page needs to be replaced page in the front of the queue is
selected for removal.

# LRU

A good approximation to the optimal algorithm is based on the observation that pages
that have been heavily used in the last few instructions will probably be heavily used
again in the next few. Conversely, pages that have not been used for ages will probably
remain unused for a long time. This idea suggests a realizable algorithm: when a page
fault occurs, throw out the page that has been unused for the longest time.

# Clock

Apart from LRU, OPT and FIFO page replacement policies, we also have the
second chance/clock page replacement policy. In the Second Chance page
replacement policy, the candidate pages for removal are considered in a round
robin matter, and a page that has been accessed between consecutive
considerations will not be replaced. The page replaced is the one that, when
considered in a round robin matter, has not been accessed since its last
consideration.
