#! gnuplot.exe

# create temporary folder
sys("mkdir _tmp")

# set terminal
set terminal epslatex standalone ",10" lw 2.5 size 5in, 8in header \
'\usepackage{amssymb, amsmath, amsbsy, graphicx, bm}\
\usepackage[x11names]{xcolor}'

# output pdf name
output_name = "fig_M1"
set output "_tmp/".output_name.".tex"
#######################################################
set multiplot

# set size 4*0.16, 3*0.16
set origin 0,0.32   # 设置放置点

set size ratio 1.5/4.0

set xlabel '\Large{$  $}' 
set ylabel '\Large{$\xi_a / L$}'   offset 2,0
set pointsize 1.0

# set key left top
set key spacing 1
set key samplen 1.5

set xrange [0.50:1.23]
set yrange [0:1.45]

set xtics ('  ' 0.5, '  ' 0.7, '  ' 0.9, '  ' 1.1, '  ' 1.3)

set ytics ('\large{$0 $}' 0, '\large{$0.4 $}' 0.4, '\large{$0.8 $}' 0.8, '\large{$1.2 $}' 1.2)

set label '\Large{\textbf{(a)}}' at graph 0.02, 0.91

set arrow 1 from 0.696, graph 0 to 0.696, graph 1 nohead lw 5.5 lc 'gray'
# set arrow 2 from 0.693, graph 0 to 0.694, graph 1 nohead 
# set arrow 3 from 0.699, graph 0 to 0.698, graph 1 nohead 

set arrow 2 from 0.91, graph 0 to 0.91, graph 1 nohead lw 1.1 dt 2 lc -1


set label '\large{$J = 0.91$}' at graph 0.33, 0.08

# set arrow 3 from  0.63, 0.495 to  0.68, 0.58 lw 1.0  lc 'black' front

set arrow 4 from  0.86, 0.15 to  0.9, 0.2 lw 1.0  lc 'black' front


set tics front

shift = 0.02

col = 33
K = '1.0'
plot  '../data_H/cmp/cmp_L_32_K_'.K.'.dat' using 2:(1.0/ (2 * $5 * sin(3.14159/$5)) * sqrt($13 / $23 - 1.0) ):(column(col + 1))  with errorline pt 4  lc '#4DAF4A'  t '$L$ = 32' at graph 0.13, 0.8 - shift ,\
'../data_H/cmp/cmp_L_64_K_'.K.'.dat' using 2:(1.0/ (2 * $5 * sin(3.14159/$5)) * sqrt($13 / $23 - 1.0) ):(column(col + 1))  with errorline pt 6  lc '#377EB8'  t '64' at graph 0.13, 0.72 - shift,\
'../data_H/cmp/cmp_L_128_K_'.K.'.dat' using 2:(1.0/ (2 * $5 * sin(3.14159/$5)) * sqrt($13 / $23 - 1.0) ):(column(col + 1))  with errorline pt 8  lc '#E41A1C'  t '128' at graph 0.13, 0.64 - shift,\
'../data_H/cmp/cmp_L_256_K_'.K.'.dat' using 2:(1.0/ (2 * $5 * sin(3.14159/$5)) * sqrt($13 / $23 - 1.0) ):(column(col + 1))  with errorline pt 10  lc 'brown'  t '256' at graph 0.13, 0.56 - shift,\
'../data_H/cmp/cmp_L_512_K_'.K.'.dat' using 2:(1.0/ (2 * $5 * sin(3.14159/$5)) * sqrt($13 / $23 - 1.0) ):(column(col + 1))  with errorline pt 12  lc 'black'  t '512' at graph 0.13, 0.48 - shift
####################>>>>>>>>>>>>>>>>>
reset

set size 2.0*0.24, 3.5*0.24
set origin 0.512,0.403  # 设置放置点

set size ratio 2.0/3.5

set xlabel '\small{$1/ \ln^{2} (L/L_0)$}' offset 0,1.4
set ylabel '\small{$J(L)$}' offset 5.8,0

set pointsize 1.0

# unset key
# unset xtics
set xtics

set xrange [-0.0001:0.052]
# set xrange [-0.0001:0.052]
set yrange [0.56:0.72]

set xtics ('\scriptsize{0}' 0,  '\scriptsize{0.04}' 0.04, '\scriptsize{0.06}' 0.06) offset 0,0.6

set ytics ('\scriptsize{0.58}' 0.58, '\scriptsize{0.70}' 0.7) offset 0.3,0

C1 = 0
b1 = 0

set label '\small{$J_{c1} = 0.699(4)$}' at graph 0.425, 0.75

set key left bottom
set key spacing 0.7
set key samplen 1.5

f(x) =  0.69967296 + -2.51869465 * x
g(x) = 0.69819382 + -2.30353990 * x

plot 0.699 lw 5 lc 'gray' notit,\
'fit_a_K_1_val_0.4.txt' using (log(5.75865779*$1)**-2.0):2:3  with error pt 4  lc 'olive'  t '\scriptsize{$0.4$}' at graph 0.4, 0.11,\
f(x) lc 'olive' notit,\
'fit_a_K_1_val_0.5.txt' using (log(8.15304569*$1)**-2.0):2:3  with error pt 6  lc 'dark-orange'  t '\scriptsize{$\xi_a/L=0.5$}' at graph 0.4, 0.21,\
g(x) lc 'dark-orange' notit,\


#######################################################
reset
# set size 4*0.16, 3*0.16
set origin 0,0.133   # 设置放置点

set size ratio 1.5/4.0

set xlabel '\Large{$  $}' 
set ylabel '\Large{$\xi_p / L$}'  offset 2,0 
set pointsize 1.0

set key right bottom
set key spacing 1
set key samplen 1.5

set xrange [0.50:1.23]
set yrange [0:0.68]

set xtics ('  ' 0.5, '  ' 0.7, '  ' 0.9, '  ' 1.1, ' ' 1.3)

set ytics ('\large{$0 $}' 0, '\large{$0.2 $}' 0.2, '\large{$0.4 $}' 0.4, '\large{$0.6 $}' 0.6)

set label '\Large{\textbf{(b)}}' at graph 0.02, 0.91
set label '\large{$K = 1$}' at graph 0.08, 0.7

set arrow 1 from 0.696, graph 0 to 0.696, graph 1 nohead lw 5.5 lc 'gray'
set arrow 2 from 0.91, graph 0 to 0.91, graph 1 nohead lw 1.1 dt 2 lc -1

set tics front

unset key

col = 39
K = '1.0'
plot  '../data_H/cmp/cmp_L_32_K_'.K.'.dat' using 2:(1.0/ (2 * $5 * sin(3.14159/$5)) * sqrt($19 / $29 - 1.0) ):(column(col + 1))  with errorline pt 4  lc '#4DAF4A'  t '32',\
'../data_H/cmp/cmp_L_64_K_'.K.'.dat' using 2:(1.0/ (2 * $5 * sin(3.14159/$5)) * sqrt($19 / $29 - 1.0) ):(column(col + 1))  with errorline pt 6  lc '#377EB8'  t '64',\
'../data_H/cmp/cmp_L_128_K_'.K.'.dat' using 2:(1.0/ (2 * $5 * sin(3.14159/$5)) * sqrt($19 / $29 - 1.0) ):(column(col + 1))  with errorline pt 8  lc '#E41A1C'  t '128',\
'../data_H/cmp/cmp_L_256_K_'.K.'.dat' using 2:(1.0/ (2 * $5 * sin(3.14159/$5)) * sqrt($19 / $29 - 1.0) ):(column(col + 1))  with errorline pt 10  lc 'brown'  t '256',\
'../data_H/cmp/cmp_L_512_K_'.K.'.dat' using 2:(1.0/ (2 * $5 * sin(3.14159/$5)) * sqrt($19 / $29 - 1.0) ):(column(col + 1))  with errorline pt 12  lc 'black'  t '512',\

# plot  '../data_H/cmp/cmp_L_32_K_'.K.'.dat' using 2:(column(col)):(column(col + 1))  with errorline pt 4  lc '#4DAF4A'  t '32',\
# '../data_H/cmp/cmp_L_64_K_'.K.'.dat' using 2:(column(col)):(column(col + 1))  with errorline pt 6  lc '#377EB8'  t '64',\
# '../data_H/cmp/cmp_L_128_K_'.K.'.dat' using 2:(column(col)):(column(col + 1))  with errorline pt 8  lc '#E41A1C'  t '128',\
# '../data_H/cmp/cmp_L_256_K_'.K.'.dat' using 2:(column(col)):(column(col + 1))  with errorline pt 10  lc 'brown'  t '256',\
# '../data_H/cmp/cmp_L_512_K_'.K.'.dat' using 2:(column(col)):(column(col + 1))  with errorline pt 12  lc 'black'  t '512',\
####################>>>>>>>>>>>>>>>>>
reset

set size 2.0*0.24, 3.5*0.24
set origin 0.512,0.215  # 设置放置点

set size ratio 2.0/3.5

set xlabel '\small{$1/ \ln^{2} (L/L_0)$}' offset 0,1.5
set ylabel '\small{$J(L)$}' offset 5.8,0

set pointsize 1.0

unset key
# unset xtics
set xtics

set xrange [-0.0001:0.075]
set yrange [0.56:0.715]

set xtics ('\scriptsize{0}' 0, '\scriptsize{0.06}' 0.06) offset 0,0.6

set ytics ('\scriptsize{0.58}' 0.58, '\scriptsize{0.70}' 0.7) offset 0.3,0

set key left bottom
set key spacing 0.7
set key samplen 1.5

set label '\small{$J_{c2} = 0.692(2)$}' at graph 0.425, 0.75

f(x) =  0.69364050 + -1.52842493 * x
g(x) = 0.69419674 + -0.19029450 * x
k(x) = 0.69082606 + -0.89432027 * x

plot 0.692 lw 3 lc 'gray' notit,\
'fit_p_K_1_val_0.2.txt' using (log(3.85411328*$1)**-2.0):2:3  with error pt 4  lc 'olive'  t '\scriptsize{0.2}' at graph 0.43, 0.11,\
f(x) lc 'olive' notit,\
'fit_p_K_1_val_0.25.txt' using (log(3.27608664*$1)**-2.0):2:3  with error pt 6  lc 'dark-orange'  t '\scriptsize{$\xi_p/L=0.25$}' at graph 0.43, 0.21,\
k(x) lc 'dark-orange' notit,\

# 'fit_p_K_1_val_0.3.txt' using (log(1.07089569*$1)**-2.0):2:3  with error pt 6  lc 'dark-orange'  t '\scriptsize{0.3}',\
# g(x) lc 'dark-orange' notit,\



#######################################################
reset

# set size 4*0.16, 3*0.16
set origin 0,-0.054   # 设置放置点

set size ratio 1.5/4.0

set pointsize 1.0

set xlabel '\Large{$J$}' 
set ylabel '\Large{$R_{M, 4}$}'  offset 2,0

# set key left bottom
set key spacing 1
set key samplen 1.5

# set logscale y

set xrange [0.50:1.23]
set yrange [0:0.68]

set xtics ('\large{0.5}' 0.5, '\large{0.7}' 0.7, '\large{0.9}' 0.9, '\large{1.1}' 1.1, '\large{1.3}' 1.3)

set ytics ('\large{$0 $}' 0, '\large{$0.2 $}' 0.2, '\large{$0.4 $}' 0.4, '\large{$0.6 $}' 0.6)

set label '\Large{\textbf{(c)}}' at graph 0.02, 0.91

set label '\large{$J_c = 0.696(3)$}' at graph 0.02, 0.65

# set label '\large{$0.91$}' at graph 0.42, 0.14

# set arrow from  0.63, 0.495 to  0.68, 0.58 lw 1.0  lc 'black' front

# set arrow from  0.86, 0.15 to  0.9, 0.2 lw 1.0  lc 'black' front

set arrow from 0.696, graph 0 to 0.696, graph 1 nohead lw 5.5 lc 'gray'
set arrow from 0.91, graph 0 to 0.91, graph 1 nohead lw 1.1 dt 2 lc -1

# set arrow 2 from  0.62, 0.5 to  0.69, 0.55 lw 1.0  lc 'black' front

set tics front

unset key

K = '1.0'
plot '../data_H/cmp/cmp_L_32_K_'.K.'.dat' using 2:(($13)**4.0 / $19)  with errorline pt 4  lc '#4DAF4A' t '32',\
'../data_H/cmp/cmp_L_64_K_'.K.'.dat' using 2:(($13)**4.0 / $19)  with errorline pt 6  lc '#377EB8' t '64',\
'../data_H/cmp/cmp_L_128_K_'.K.'.dat' using 2:(($13)**4.0 / $19)  with errorline pt 8  lc '#E41A1C'  t '128',\
'../data_H/cmp/cmp_L_256_K_'.K.'.dat' using 2:(($13)**4.0 / $19)  with errorline pt 10  lc 'brown' t '256',\
'../data_H/cmp/cmp_L_512_K_'.K.'.dat' using 2:(($13)**4.0 / $19)  with errorline pt 12  lc 'black' t '512',\
####################>>>>>>>>>>>>>>>>>
reset

set size 2.0*0.24, 3.5*0.24
set origin 0.512,0.03   # 设置放置点

set size ratio 2.0/3.5

set xlabel '\small{$r$}'  offset 0,1.3
set ylabel '\small{$R_{g, 4}$}'  offset 5.8,0

set pointsize 0.75

unset key

set logscale xy

set yrange [0 : 1]

set xtics ('\scriptsize{$1$}' 1, '\scriptsize{$100$}' 100) offset 0,0.25

set ytics ('\scriptsize{$0.10$}' 0.1, '\scriptsize{$1.00$}' 1) offset 0.5,0

set label '\small{$J = 0.8$}' at graph 0.08, 0.35



K = '1'
J = '0.8'

plot '../data_Rgk/CorrR_L_32_K_'.K.'_J_'.J.'_k_4.0.dat' using 1:(1.0/$2)  with errorline pt 4  lc '#4DAF4A'  notit,\
'../data_Rgk/CorrR_L_64_K_'.K.'_J_'.J.'_k_4.0.dat' using 1:(1.0/$2)  with errorline pt 6  lc '#377EB8'  notit,\
'../data_Rgk/CorrR_L_128_K_'.K.'_J_'.J.'_k_4.0.dat' using 1:(1.0/$2)  with errorline pt 8  lc '#E41A1C'  notit,\
'../data_Rgk/CorrR_L_256_K_'.K.'_J_'.J.'_k_4.0.dat' using 1:(1.0/$2)  with errorline pt 10  lc 'brown'  notit,\
'../data_Rgk/CorrR_L_512_K_'.K.'_J_'.J.'_k_4.0.dat' using 1:(1.0/$2)  with errorline pt 12  lc 'black'  notit,\

#######################################################
unset multiplot
unset output

# make pdf and png
output_name = '_tmp/'.output_name
sys(sprintf("pdflatex-dev.exe --aux-directory=_tmp %s.tex", output_name))