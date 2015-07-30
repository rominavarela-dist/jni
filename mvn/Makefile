##########################################################
### java
java_NAME = JNIWrapper
java_PACKAGE = com.hp.hpl.jni.
java_BUILD_DIR = /home/romina1/workspace/test\ apps/JNITestService/target/classes/

##########################################################
### c
c_NAME = wrapper
c_SRC_DIRS = ./src/
c_BUILD_DIR = /mirror/romina/workspace/demo/jni/mvn/out/

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
	mkdir -p $(c_BUILD_DIR)
	mkdir -p $(c_BUILD_DIR)
	javah -classpath $(java_BUILD_DIR) -d $(c_BUILD_DIR) -jni $(java_PACKAGE)$(java_NAME)
	$(CXX) $(CXXFLAGS) $(c_SRCS) $(LDFLAGS) $(CPPFLAGS) -o $(c_BUILD_DIR)lib$(c_NAME).so

run:
	java -Djava.library.path=$(c_BUILD_DIR) -classpath $(java_BUILD_DIR) $(java_NAME)
