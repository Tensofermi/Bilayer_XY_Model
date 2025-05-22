#! gnuplot.exe

# create temporary folder
sys("mkdir _tmp")

# set terminal
set terminal epslatex standalone ",10" lw 3 size 5in, 5in header \
'\usepackage{amssymb, amsmath, amsbsy, graphicx, bm}\
\usepackage[x11names]{xcolor}'

# output pdf name
output_name = "fig_M2_eta_p"
set output "_tmp/".output_name.".tex"
#######################################################
set multiplot

# set size 4*0.16, 3*0.16
# set origin 0,0.3   # 设置放置点

set size ratio 2.5/4.0

set xlabel '\Large{$L$}' 
set ylabel '\Large{$\langle M^2_p \rangle$}'   offset 2,0
set pointsize 1.3

set logscale xy
set key right top
set key spacing 0.9
set key samplen 1.5
# set key at graph -0.07,0.03

mp_0 = 0.5203820484424206
mp_1 = 0.5237489521607384
mp_2 = 0.5086591906681047
mp_3 = 0.4754754991321095
mp_4 = 0.3876982299356050
mp_5 = 0.3185576258945063
mp_6 = 0.2725833749819881

set xrange [15:300]
set yrange [0.13:0.61]

set xtics ('\large{$16$}' 16,'\large{$64$}' 64, '\large{$256$}' 256)

set ytics ('\large{$0.15$}' 0.15, '\large{$0.35$}' 0.35, '\large{$0.55$}' 0.55) offset 0.5,0

# set label '\Large{(a)}' at graph 0.02, 0.92
col = 19
# unset key
plot  '../data_P_eta/cmp/cmp_J_0.00000_K_1.12100.dat' using 5:(column(col)):(column(col + 1))  with errorline pt 2  lc 'olive'  t '$K, J$ = 1.121, 0.000',\
'../data_P_eta/cmp/cmp_J_0.30000_K_1.07100.dat' using 5:(mp_0/mp_1 * column(col)):(mp_0/mp_1 * column(col + 1))  with errorline pt 4  lc '#E41A1C'  t '1.071, 0.300',\
'../data_P_eta/cmp/cmp_J_0.49800_K_0.90000.dat' using 5:(mp_0/mp_2 * column(col)):(mp_0/mp_2 * column(col + 1))  with errorline pt 6  lc '#377EB8'  t '0.900, 0.498',\
'../data_P_eta/cmp/cmp_J_0.59700_K_0.75000.dat' using 5:(mp_0/mp_3 * column(col)):(mp_0/mp_3 * column(col + 1))  with errorline pt 8  lc  '#4DAF4A' t '0.750, 0.597',\
'../data_P_eta/cmp/cmp_J_0.74000_K_0.50000.dat' using 5:(mp_0/mp_4 * column(col)):(mp_0/mp_4 * column(col + 1))  with errorline pt 10  lc 'dark-orange '  t '0.500, 0.740',\
'../data_P_eta/cmp/cmp_J_0.97000_K_0.20000.dat' using 5:(mp_0/mp_5 * column(col)):(mp_0/mp_5 * column(col + 1))  with errorline pt 12  lc 'dark-blue'  t '0.200, 0.970',\
'../data_P_eta/cmp/cmp_J_1.11900_K_0.00000.dat' using 5:(mp_0/mp_6 * column(col)):(mp_0/mp_6 * column(col + 1))  with errorline pt 14  lc 'black'  t '0.000, 1.119',\
# 1.9*x**(-0.50) t 'slope -0.50'
# 1.15*x**(-0.25) t 'slope -0.25',\

####################>>>>>>>>>>>>>>>>>
reset

set size 2.5*0.18, 4*0.18
set origin 0.09,0.04   # 设置放置点

set size ratio 2.5/4.0

set xlabel '\small{$K$}'    offset 0,1.2
set ylabel '\small{$\eta_p$}'   offset 3,0
set pointsize 1
set key left top
set key spacing 1
set key samplen 2

set xrange [-0.01:1.2]
set yrange [0.18:0.55]

set xtics ('\scriptsize{0}' 0, '\scriptsize{0.4}' 0.4, '\scriptsize{0.8}' 0.8, '\scriptsize{1.2}' 1.2) offset 0, 0.5

set ytics ('\scriptsize{0.2}' 0.2, '\scriptsize{0.3}' 0.3, '\scriptsize{0.4}' 0.4, '\scriptsize{0.5}' 0.5) offset 0.5, 0


col = 33
K = '1.0'
plot  'eta_p.txt' using 4:2:3  with error pt 6  lc 'olive'  notit,\
0.25 lc 'dark-green' dt 2 notit,\
0.5 lc 'dark-blue' dt 2 notit
#######################################################
#######################################################
unset multiplot
unset output

# make pdf and png
output_name = '_tmp/'.output_name
sys(sprintf("pdflatex-dev.exe --aux-directory=_tmp %s.tex", output_name))