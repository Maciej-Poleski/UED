#include <Core.hxx>

int main(int argc, char *argv[])
{
    (new Core::Core(argc,argv))->install();
    return Core::core->run();
}
