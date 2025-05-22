#! gnuplot.exe

# create temporary folder
sys("mkdir _tmp")

# set terminal
set terminal epslatex standalone ",10" lw 3 size 5in, 6in header \
'\usepackage{amssymb, amsmath, amsbsy, graphicx, bm}\
\usepackage[x11names]{xcolor}'

# output pdf name
output_name = "fig_M2"
set output "_tmp/".output_name.".tex"
set size ratio 1.5/4.0
#######################################################
set multiplot

# set size 4*0.16, 3*0.16
set origin 0,0.298   # 设置放置点

LRO =      '#b0c4de'
QLRO =     '#99fe99'
Disorder = '#ffdb99'

Order1 =       '#2F4F4F'
Order2 =       '#4B0082'
nonClassical = 'red'
Orderinf =     'brown'

set key left top

set pointsize 1.2
# set pointintervalbox 0.0001

set xlabel '\Large{$ $}' 
set ylabel '\Large{$\xi_a / L$}' offset 0.8,0

set xtics ('\Large{ }' 0.40, '\Large{ }' 0.5, '\Large{ }' 0.6, '\Large{ }' 0.7)
set ytics ('\large{0}' 0, '\large{0.5}' 0.5, '\large{1.0}' 1, '\large{1.5}' 1.5, '\large{1.6}' 1.6)

set arrow from 0.499, graph 0 to 0.499, graph 1 nohead dt 6 lw 0.9

# set arrow from 0.605, graph 0 to 0.605, graph 1 nohead 
set arrow from 0.607, graph 0 to 0.607, graph 1 nohead lw 5.2 lc 'gray'
# set arrow from 0.609, graph 0 to 0.609, graph 1 nohead 

set label '\large{$J_{c1} = 0.607(2)$}' at 0.615, 0.2

set arrow from  0.65, 0.3 to  0.615, 0.45 lw 1.0  lc 'black' front

set tics front

set xrange [0.34:0.71]
set yrange [0:1.2]

set key spacing 0.9
set key samplen 1.5

set label '\Large{\textbf{(a)}}' at graph 0.92, 0.9

set tics front

col = 33
K = '0.90000'
shift_ = 0.3
plot  '../data_P/cmp/cmp_L_16_K_'.K.'.dat' using 2:(1.0/ (2 * $5 * sin(3.14159/$5)) * sqrt($13 / $23 - 1.0) ):(column(col + 1))  with errorline pt 4  lc '#4DAF4A'  t '$L$ = 16',\
'../data_P/cmp/cmp_L_32_K_'.K.'.dat' using 2:(1.0/ (2 * $5 * sin(3.14159/$5)) * sqrt($13 / $23 - 1.0) ):(column(col + 1))  with errorline pt 6  lc '#377EB8'  t '32',\
'../data_P/cmp/cmp_L_64_K_'.K.'.dat' using 2:(1.0/ (2 * $5 * sin(3.14159/$5)) * sqrt($13 / $23 - 1.0) ):(column(col + 1))  with errorline pt 8  lc '#E41A1C'  t '64',\
'../data_P/cmp/cmp_L_128_K_'.K.'.dat' using 2:(1.0/ (2 * $5 * sin(3.14159/$5)) * sqrt($13 / $23 - 1.0) ):(column(col + 1))  with errorline pt 10  lc 'brown'  t '128',\
'../data_P/cmp/cmp_L_256_K_'.K.'.dat' using 2:(1.0/ (2 * $5 * sin(3.14159/$5)) * sqrt($13 / $23 - 1.0) ):(column(col + 1))  with errorline pt 12  lc 'black'  t '256',\

####################>>>>>>>>>>>>>>>>>
reset

set size 1.5*0.38, 2.0*0.38
set origin -0.0148,-0.126 - 0.008   # 设置放置点

set size ratio 1.5/2.0

set xlabel '\Large{$r$}'  offset 0,0.4
set ylabel '\Large{$g_a(r)$}'  offset 5,0

set pointsize 1.

unset key
set logscale xy
# set logscale xy2
# set y2tics
set yrange [2e-5 : 1.5]
set xrange [1:200]
# set y2range [1e-6 : 1]
# unset ytics
set xtics ('\large{$10^0$}' 1, '\large{$10^1$}' 10, '\large{$10^2$}' 100) offset 0,0.
# set ytics ('\Large{$10^0$}' 1, '\Large{$10^{-3}$}' 1e-3, '\Large{$10^{-6}$}' 1e-6) offset 0.5,0
set ytics ('\large{$10^0$}' 1, '\large{$10^{-4}$}' 1e-4, '\large{$10^{-6}$}' 1e-6) offset 0.8,0

set label '\Large{$J = 0.5$}' at graph 0.05, 0.40
set label '\Large{\textbf{(c)}}' at graph 0.82, 0.89
# set label '\small{$g_a(r)$ vs. $r$}' at graph 0.08, 0.15

K = '0.9'
J = '0.5'

plot '../data_P/data_Corr/CorrFun_L_16_K_'.K.'_J_'.J.'.dat' using 1:2  with errorline pt 4  lc '#4DAF4A'  notit,\
'../data_P/data_Corr/CorrFun_L_32_K_'.K.'_J_'.J.'.dat' using 1:2  with errorline pt 6  lc '#377EB8'  notit,\
'../data_P/data_Corr/CorrFun_L_64_K_'.K.'_J_'.J.'.dat' using 1:2  with errorline pt 8  lc '#E41A1C'  notit,\
'../data_P/data_Corr/CorrFun_L_128_K_'.K.'_J_'.J.'.dat' using 1:2  with errorline pt 10  lc 'brown'  notit,\
'../data_P/data_Corr/CorrFun_L_256_K_'.K.'_J_'.J.'.dat' using 1:2  with errorline pt 12  lc 'black'  notit,\


reset

set size ratio 1.5/4.0

# set size 4*0.16, 3*0.16
set origin 0,0.054  # 设置放置点


set pointsize 1.2

set xlabel '\Large{$J$}' offset 0, 0.9
set ylabel '\Large{$\xi_p / L$}' offset 0.8,0

set xtics ('\large{0.40}' 0.40, '\large{0.50}' 0.5, '\large{0.60}' 0.6, '\large{0.70}' 0.7)
set ytics ('\large{0}' 0, '\large{0.5}' 0.5, '\large{1.0}' 1.0, '\large{1.5}' 1.5, '\large{1.6}' 1.6)

set arrow from 0.607, graph 0 to 0.607, graph 1 nohead dt 6 lw 0.9

# set arrow from 0.498 - 0.002, graph 0 to 0.498 - 0.002, graph 1 nohead
set arrow from 0.499, graph 0 to 0.499, graph 1 nohead lw 5.2 lc 'gray'
# set arrow from 0.498 + 0.002, graph 0 to 0.498 + 0.002, graph 1 nohead

set tics front

set label '\Large{$K = 0.9$}' at graph 0.08, 0.82

set xrange [0.34:0.71]
set yrange [0:1.2]

set label '\Large{\textbf{(b)}}'  at graph 0.92, 0.9

set label '\large{$J_{c2} = 0.499(2)$}' at 0.505, 0.2

set arrow from  0.54, 0.3 to  0.505, 0.45 lw 1.0  lc 'black' front

set tics front
unset key

col = 39
K = '0.90000'
plot  '../data_P/cmp/cmp_L_16_K_'.K.'.dat' using 2:(1.0/ (2 * $5 * sin(3.14159/$5)) * sqrt($19 / $29 - 1.0) ):(column(col + 1))  with errorline pt 4  lc '#4DAF4A'  t '16',\
'../data_P/cmp/cmp_L_32_K_'.K.'.dat' using 2:(1.0/ (2 * $5 * sin(3.14159/$5)) * sqrt($19 / $29 - 1.0) ):(column(col + 1))  with errorline pt 6  lc '#377EB8'  t '32',\
'../data_P/cmp/cmp_L_64_K_'.K.'.dat' using 2:(1.0/ (2 * $5 * sin(3.14159/$5)) * sqrt($19 / $29 - 1.0) ):(column(col + 1))  with errorline pt 8  lc '#E41A1C'  t '64',\
'../data_P/cmp/cmp_L_128_K_'.K.'.dat' using 2:(1.0/ (2 * $5 * sin(3.14159/$5)) * sqrt($19 / $29 - 1.0) ):(column(col + 1))  with errorline pt 10  lc 'brown'  t '128',\
'../data_P/cmp/cmp_L_256_K_'.K.'.dat' using 2:(1.0/ (2 * $5 * sin(3.14159/$5)) * sqrt($19 / $29 - 1.0) ):(column(col + 1))  with errorline pt 12  lc 'black'  t '256',\
####################>>>>>>>>>>>>>>>>>
reset

set size 1.5*0.38, 2.0*0.38
set origin 0.43, -0.126 - 0.008  # 设置放置点

set size ratio 1.5/2.0

set xlabel '\Large{$r$}'  offset 0,0.4
set ylabel '\Large{$g_p(r)$}'  offset 5,0

set pointsize 1

unset key

set logscale xy

set xrange [1:200]
set yrange [0.1 : 1.1]

set xtics ('\large{$10^0$}' 1, '\large{$10^1$}' 10, '\large{$10^2$}' 100) offset 0,0.

set ytics ('\large{$10^0$}' 1, '\large{$10^{-1}$}' 1e-1, '\large{$10^{-4}$}' 1e-4, '\large{$10^{-6}$}' 1e-6) offset 0.8,0

set label '\Large{$J = 0.5$}' at graph 0.05, 0.40
set label '\Large{\textbf{(d)}}' at graph 0.82, 0.89

# set label '\small{$g_p(r)$ vs. $r$}' at graph 0.08, 0.15

K = '0.9'
J = '0.5'

plot '../data_P/data_Corr/CorrPair_L_16_K_'.K.'_J_'.J.'.dat' using 1:2  with errorline pt 4  lc '#4DAF4A'  notit,\
'../data_P/data_Corr/CorrPair_L_32_K_'.K.'_J_'.J.'.dat' using 1:2  with errorline pt 6  lc '#377EB8'  notit,\
'../data_P/data_Corr/CorrPair_L_64_K_'.K.'_J_'.J.'.dat' using 1:2  with errorline pt 8  lc '#E41A1C'  notit,\
'../data_P/data_Corr/CorrPair_L_128_K_'.K.'_J_'.J.'.dat' using 1:2  with errorline pt 10  lc 'brown'  notit,\
'../data_P/data_Corr/CorrPair_L_256_K_'.K.'_J_'.J.'.dat' using 1:2  with errorline pt 12  lc 'black'  notit,\
0.710465*x**(-0.25) lc 'olive'
# ####################>>>>>>>>>>>>>>>>>


#######################################################
unset multiplot
unset output

# make pdf and png
output_name = '_tmp/'.output_name
sys(sprintf("pdflatex-dev.exe --aux-directory=_tmp %s.tex", output_name))