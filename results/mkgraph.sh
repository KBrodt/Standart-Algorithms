#!/usr/bin/gnuplot

datafile01 = "insertionsort.dat"
datafile02 = "selectionsort.dat"
datafile03 = "bubblesort.dat"
datafile04 = "mergesort.dat"
datafile05 = "heapsort.dat"
#datafile06 = ""
datafile07 = "countingsort.dat"
datafile08 = "radixsortBIN8.dat"

set terminal png size 800,480 enhanced font 'Arial, 16'
set output 'sort.png'

#set style line 1 linecolor rgb 'red' linetype 1 linewidth 2
#set style line 2 linecolor rgb 'blue' linetype 1 linewidth 2

set border linewidth 1
set key top left
set grid
set mytics 0
set format y "%.3f"
set xlabel "Number of elements" font "Arial, 16"
set format x "%g"# "%.0f"
set ylabel "Execution time (sec)" font "Arial, 16"
set xtics 10000000 font "Arial, 12"
set ytics font "Arial, 12"
set rmargin 4
set tmargin 2
set mxtics

#plot datafile01 u 1:2 t "Insertion Sort" w lp ls 1,\
#     datafile02 u 1:2 t "Selection Sort" w lp ls 2,\
#     datafile03 u 1:2 t "Bubble Sort" w lp ls 3
plot datafile04 u 1:2 t "Merge Sort" w lp ls 4,\
     datafile05 u 1:2 t "Heap Sort" w lp ls 5,\
     datafile07 u 1:2 t "Counting Sort" w lp ls 7,\
     datafile08 u 1:2 t "Radix Sort" w lp ls 8,\
