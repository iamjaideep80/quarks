################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/forces/DragForce.cpp \
../src/forces/Force.cpp \
../src/forces/ForceData.cpp \
../src/forces/ForceFactory.cpp \
../src/forces/NoiseForce.cpp \
../src/forces/UniformForce.cpp \
../src/forces/VDBForce.cpp \
../src/forces/VortexForce.cpp 

OBJS += \
./src/forces/DragForce.o \
./src/forces/Force.o \
./src/forces/ForceData.o \
./src/forces/ForceFactory.o \
./src/forces/NoiseForce.o \
./src/forces/UniformForce.o \
./src/forces/VDBForce.o \
./src/forces/VortexForce.o 

CPP_DEPS += \
./src/forces/DragForce.d \
./src/forces/Force.d \
./src/forces/ForceData.d \
./src/forces/ForceFactory.d \
./src/forces/NoiseForce.d \
./src/forces/UniformForce.d \
./src/forces/VDBForce.d \
./src/forces/VortexForce.d 


# Each subdirectory must supply rules for building sources it contributes
src/forces/%.o: ../src/forces/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


