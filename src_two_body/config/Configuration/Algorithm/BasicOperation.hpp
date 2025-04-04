#pragma once

/* ------------------------------------------------------------------------------------*/
/* ---------------------------------- Spin Operation ----------------------------------*/
/* ------------------------------------------------------------------------------------*/

double Configuration::randAngle()
{
    // Angle \in [-π, π)
    return rn.getRandomDouble(0, 2 * M_PI)  - M_PI;
}

void Configuration::randRotation()
{
    double theta = randAngle();
    for (int i = 0;  i < Vol; i++)
    {
        Site[i] = modAngle(Site[i] + theta);
    }
}

void Configuration::yaxisFlip(long _site)
{
    Site[_site] = modAngle( - Site[_site]);
}

void Configuration::pointFlip(long _site)
{
    Site[_site] = modAngle(Site[_site] + M_PI);
}