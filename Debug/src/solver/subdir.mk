################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/solver/ForceManager.cpp \
../src/solver/OdeSolver.cpp \
../src/solver/ParticleSystem.cpp \
../src/solver/SoftBodyManager.cpp \
../src/solver/SourceManager.cpp 

OBJS += \
./src/solver/ForceManager.o \
./src/solver/OdeSolver.o \
./src/solver/ParticleSystem.o \
./src/solver/SoftBodyManager.o \
./src/solver/SourceManager.o 

CPP_DEPS += \
./src/solver/ForceManager.d \
./src/solver/OdeSolver.d \
./src/solver/ParticleSystem.d \
./src/solver/SoftBodyManager.d \
./src/solver/SourceManager.d 


# Each subdirectory must supply rules for building sources it contributes
src/solver/%.o: ../src/solver/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


