void macro1()
{
    TF1 *f1 = new TF1("f1", "[0]*sin([1]*x)/([1]*x)", 0, 10);
    f1->SetParameter(0,2);
    f1->SetParameter(1,2);
    f1->Draw();

};

int main()
{
    macro1();
    return 0;
}