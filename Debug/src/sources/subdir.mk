################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/sources/SoftBodyData.cpp \
../src/sources/SoftBodySource.cpp \
../src/sources/Source.cpp \
../src/sources/SourceData.cpp \
../src/sources/SourceFactory.cpp \
../src/sources/SphereSource.cpp \
../src/sources/VDBSource.cpp 

OBJS += \
./src/sources/SoftBodyData.o \
./src/sources/SoftBodySource.o \
./src/sources/Source.o \
./src/sources/SourceData.o \
./src/sources/SourceFactory.o \
./src/sources/SphereSource.o \
./src/sources/VDBSource.o 

CPP_DEPS += \
./src/sources/SoftBodyData.d \
./src/sources/SoftBodySource.d \
./src/sources/Source.d \
./src/sources/SourceData.d \
./src/sources/SourceFactory.d \
./src/sources/SphereSource.d \
./src/sources/VDBSource.d 


# Each subdirectory must supply rules for building sources it contributes
src/sources/%.o: ../src/sources/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


