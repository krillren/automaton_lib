# This small tool allows you to check the coverage of your code 
# It also allows to run several different tests coming from several different source codes


# Setup coverage
    On college computers you need to install *gcovr* with the commande :
        pip install gcovr

        Then you need to change the GCOVR variable (line 7) in the makefile
        replacing *gcovr* to something like *home/AD/mguille/.local/bin/gcovr*
        (don't forget to replace mguille by your own name)


    On your linux computer you need to install two tools :
        *gcc* with the pakage manager of your distribution
            sudo dnf install gcc-c++
            or
            sudo apt install build-essential
            (good luck with arch distrib)
            You should already have it

        *gcovr* with pip the python package installer
            sudo pip install gcovr
        If you don't have pip instaled, install it
            sudo dnf install pip
            sudo apt install pip

        If you don't want add *gcovr* to your $PATH, you must modify the makefile of the *Coverage* folder.
        Change the GCOVR variable to the path of the gcovr executable. (line 7)
        You can find the *gcovr* executable with the command *whereis gcovr*


    On your windows computer you have to understand something
        Bill Gates is satanic fuck Windows
        Become a Giga Chad programmer and switch to linux


    On MacOS computer you can contact me on discord (@tinouche4) to talk about money and i will install it for you
        I want to buy myself one



# How to use coverage:
-   Put the TiTouls folder into your project
-   Open terminal into TiTouls folder
-   Run make 
-   You can now open the *coverage.html* file in *Coverage* folder

# How to use mass test (give execution rights to *preparetest.sh* and *runothertest.sh*)
-   Put all your tests received in the *test* folder 
-   Use the *runothertest.sh* script, It run your program with all test from test folder
-   You can use *preparetest* to copy your test in *test* folder


# Information given in coverage
    Covered lines : 
        Percentage and number of lines covered by your test

    Covered functions : 
        Percentage and number of functions covered by your test

    Covered branchs : 
        Percentage and number of branchs covered by your test
        You can also run *make all* to generate with all possible branchs 
        This is not the default option because he is possible to some branchs can't be activated with this options.
        It's related to CPU optimization.

    Into the HTML file you have also the Covered decisions : 
        Percentage and number of conditions covered by your test
        Some decisions cannot be verified, they will be indicated to you



# To conclude
    If you have question tag @tinouche4 on discord
    If you like the act, send nude