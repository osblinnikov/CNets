cnets
=====

Messaging libraries for JAVA, C, Javascript

Dependencies for C: `Python 2.7, SCons + snocs, gcc`

Dependencies for Java: `JDK`, [maven](http://apache.vianett.no/maven/maven-3/3.2.1/binaries/apache-maven-3.2.1-bin.tar.gz)

Dependencies for Java: `npm, grulp`

Getting started:
=======

Dependencies for JavaScript: `npm, grulp`

#Getting started

    cd $FAVORITE_PROJECTS_DIR
    mkdir -p github.com/airutech
    cd github.com/airutech

    git clone --recursive https://github.com/airutech/cnets.git
    cd cnets

To build and run tests type:

for Java:

    mvn clean install

C:

    snocs compiler=gcc test
    
JavaScript:

    grulp mapBuffer/js --testlast --useconfig
