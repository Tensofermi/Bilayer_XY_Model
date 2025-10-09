#! gnuplot.exe

# create temporary folder
sys("mkdir _tmp")

# col_width_pt  = 246.0    # single column width in pt
# text_width_pt = 510.0    # text width in pt for two column figure
# inches_per_pt = 1.0/72.27                 # convert pt to inches
# figure_ratio = (sqrt(5)-1.0)/2.0          # figure_ratio
# fig_width  = col_width_pt*inches_per_pt   # width in inches
# fig_height = fig_width*figure_ratio       # height in inches

# set terminal
set terminal epslatex standalone ",10" lw 5 size 6in, 6in header \
'\usepackage{amssymb, amsmath, amsbsy, graphicx, bm}\
\usepackage[x11names]{xcolor}'

# output pdf name
output_name = "PD"
set output "_tmp/".output_name.".tex"
set size ratio 2.1/4.0
#######################################################
set multiplot

lenth = 0.35
set size 2.5*lenth, 4*lenth
set origin 0,0.04   # 设置放置点

LRO =      '#b0c4de'
QLRO =     '#2DEF81'
Disorder = '#ffdb99'

Order1 =       '#2F4F4F'
Order2 =       '#4B0082'
nonClassical = 'red'
Orderinf =     'brown'

# set lmargin 3.2
# set rmargin 0.5
# # set bmargin 1.75
# set tmargin 0.75

set pointsize 2
# set pointintervalbox 0.0001

set xlabel '\Large{$ $}' 
set ylabel '\LARGE{$J$}' offset 0.8,0

# set xtics ('\LARGE{0}' 0, '\LARGE{1}' 1, '\LARGE{2}' 2, '\LARGE{3}' 3)
set xtics ('' 0, '' 1, '' 2, '' 3)
set ytics ('\LARGE{0.5}' 0.5, '\LARGE{0.7}' 0.7, '\LARGE{0.9}' 0.9, '\LARGE{1.1}' 1.1)

# set tics front
# set tics font ",20"

set xrange [0.:3.5]
set yrange [0.4:1.2]

# set label '\LARGE{\textbf{(a)}}' at 0.1, 1.12 front
set label '\huge{{Disorder}}'  at 1.5, 0.5 front
set label '\huge{{SF}}' at 1.9, 1 front


# set label '\LARGE{\textbf{(c)}}' at 3.6, 1.12 front


# set arrow from 1, 0.5 to 1, 1.1 nohead dt 6 lw 0.9 front

set tics front

plot "H_PD_beta" u 1:2:(-100) with filledcurves  lc rgb Disorder notit ,\
"H_PD_beta" u 1:2:(100) with filledcurves  lc rgb QLRO notit ,\
'H_PD_beta' u 1:2:3 with errorline pt 14 lc rgb Orderinf notit,\
'others_1.txt' u 1:2 with l dashtype (35,50) lc 'dark-orange'  notit,\

# 'H_PD_beta' u 1:4:5 with errorline pt 16 lc rgb 'green' notit,\
# 'H_PD_beta' u 1:6:7 with errorline pt 18 lc rgb 'pink' notit,\
# 'others_2.txt' u 1:2 with l pt 16 notit,\


#######################################################
reset

set size ratio 2.1/4.0

lenth = 0.35
set size 2.5*lenth, 4*lenth
set origin 0,-0.35   # 设置放置点

LRO =      '#b0c4de'
QLRO =     '#2DEF81'
Disorder = '#ffdb99'

Order1 =       '#2F4F4F'
Order2 =       '#4B0082'
nonClassical = 'red'
Orderinf =     'brown'

set pointsize 2

set xlabel '\LARGE{$K$}' 
set ylabel '\LARGE{$J$}' offset 0.8,0

set xtics ('\LARGE{0}' 0, '\LARGE{1}' 1, '\LARGE{2}' 2, '\LARGE{3}' 3)
set ytics ('\LARGE{0}' 0, '\LARGE{0.4}' 0.4, '\LARGE{0.8}' 0.8, '\LARGE{1.2}' 1.2)

set xrange [0.:3.5]
set yrange [0.0:1.2]

set label '\LARGE{\textbf{(b)}}' at 0.1, 1.1 front
set label '\huge{{Disorder}}'  at 0.15, 0.15 front
set label '\huge{{PSF}}' at 2, 0.3 front
set label '\huge{${\text{SF}}_2$}' at 1.9, 0.9 front

# set label '\LARGE{\textbf{(d)}}' at 3.6, 1.12 front

set arrow from 0.9, 0.35 to 0.9, 0.7 nohead dt 6 lw 0.9 front

set tics front

plot "P_PD_data_1" u 1:2:4 with filledcurves  lc rgb LRO notit ,\
"P_PD_data_2" u 1:2:(-100) with filledcurves  lc rgb Disorder notit ,\
"P_PD_data_1" u 1:2:(100) with filledcurves  lc rgb QLRO notit ,\
'P_PD_data_1' u 1:2:3 with errorline pt 14 lc rgb Orderinf notit,\
'P_PD_data_2_yerror' u 1:2:3 with error pt 6 lc rgb Order1 notit,\
'P_PD_data_2_xerror' u 1:2:3 with xerror pt 6 lc rgb Order1 notit,\
'P_PD_data_2' u 1:2 with line lc rgb Order1 notit,\

#######################################################
unset multiplot
unset output

# make pdf and png
output_name = '_tmp/'.output_name
sys(sprintf("pdflatex-dev.exe --aux-directory=_tmp %s.tex", output_name))