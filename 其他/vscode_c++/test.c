#include <stdlib.h>
#include <stdio.h>

int main()
{
    FILE *fp;

    float d=0.8;
    int x=0;
    int y=0;
    int z=0;
    float z_start=0.5;
    float z_over=-2.5;
    int F_move=1000;
    int F_drill=200;

    fp=fopen("drill.txt","w");
    fprintf(fp,"G90 F%d\n S20000 M3",F_move);
    fprintf(fp,"G0 X0 Y0 Z0.5\n");
    for(y=0;y<100;)
    {
        fprintf(fp,"G0 Y%f F%d\n",float(y*d),F_move);
        y++;
        for(x=0;x<100;)
        {
            fprintf(fp,"G0 X%f F%d\n",float(x*d),F_move);
            fprintf(fp,"G1 Z%f F%d\n",z_over,F_drill);
            fprintf(fp,"G1 Z%f F%d\n",z_start,F_drill);
            x++;
        }
        fprintf(fp,"G0 Y%f F%d\n",float(y*d),F_move);
        y++;
        for(x=99;x>=0;)
        {
            fprintf(fp,"G0 X%f F%d\n",float(x*d),F_move);
            fprintf(fp,"G1 Z%f F%d\n",z_over,F_drill);
            fprintf(fp,"G1 Z%f F%d\n",z_start,F_drill);
            x--;
        }
    }

    

    fclose(fp);

    return 0;


}