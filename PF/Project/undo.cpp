struct fun
{
    int *var=new int[];
    int index=0;
    
    void undo()
    {
        index--;
    }
    void display()
    {
        cout<<var[index];
    }

};