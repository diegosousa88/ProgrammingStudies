# Sample Thread

To build Sample Thread run:

```bash
g++ SampleThread.cpp -o SampleThread -lpthread
```

In order to see thread info run ./SampleThread and then run:

```bash
top -H -p $(pgrep -d',' -f "SampleThread")
```

For more information, please watch [this video series](https://www.youtube.com/watch?v=eeSC43KQdVI).