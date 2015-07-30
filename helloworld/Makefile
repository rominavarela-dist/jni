class_DST_DIR = ./out/bin/
header_DST_DIR = ./out/include/
lib_DST_DIR = ./out/lib/

##########################################################
### java
java_NAME = JNIFoo
java_SRC_DIR = ./src/
java_SRC = $(java_SRC_DIR)$(java_NAME).java

##########################################################
### c
c_NAME = foo
c_DEST_NAME = libfoo.so
c_SRC_DIRS = ./src/

c_SRCS +=  $(foreach dir,$(c_SRC_DIRS),$(wildcard $(dir)*.c))
c_SRCS +=  $(foreach dir,$(c_SRC_DIRS),$(wildcard $(dir)*.cc))
c_SRCS +=  $(foreach dir,$(c_SRC_DIRS),$(wildcard $(dir)*.cpp))

CXXFLAGS+= -shared -fpic

##########################################################
### -I ./include
###  directory with .h, .hpp
###  include<>
program_INCLUDE_DIRS += /usr/lib/jvm/java-1.8.0-openjdk-amd64/include
program_INCLUDE_DIRS += /usr/lib/jvm/java-1.8.0-openjdk-amd64/include/linux
###  -L ./lib
###  directory with .a .so .lib .dll
program_LIBRARY_DIRS =
###  linux:   lib***.a = -l***
###  windows: lib***.lib = -lib***.lib
program_LIBRARIES =

#  include
CPPFLAGS += $(foreach includedir,$(program_INCLUDE_DIRS),-I$(includedir))
#  link
LDFLAGS += $(foreach librarydir,$(program_LIBRARY_DIRS),-L$(librarydir))
LDFLAGS += $(foreach library,$(program_LIBRARIES),-l$(library))

##########################################################
all:
	mkdir -p $(class_DST_DIR)
	mkdir -p $(header_DST_DIR)
	mkdir -p $(lib_DST_DIR)
	javac $(java_SRC) -d $(class_DST_DIR)
	javah -classpath $(class_DST_DIR) -d $(header_DST_DIR) -jni $(java_NAME)
	$(CXX) $(CXXFLAGS) $(c_SRCS) $(LDFLAGS) $(CPPFLAGS) -o $(lib_DST_DIR)$(c_DEST_NAME)

run:
	java -Djava.library.path=$(lib_DST_DIR) -classpath $(class_DST_DIR) $(java_NAME)
