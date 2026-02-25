int main ()
{
    int i;
    unsigned long int j;
    i=0;
    j=0;
    *(unsigned long*)(0x40023830) |= 0x40;
    for(i=0; i<4; i++){}
    *(unsigned long*)(0x40021800) = (*(unsigned long*)(0x40021800) &
    (~0x00008000)) | (0x00004000);

    while(1)
    {
        *(unsigned long*)(0x40021814) |= 0x80;
        for( j=0; j<2000000 ;j++ ){}
        *(unsigned long*)(0x40021814) &= ~0x80;
        for(j=0; j<2000000 ; j++){}
    }
}
