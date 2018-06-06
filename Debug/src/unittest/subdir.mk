################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/unittest/TestHoudini.cpp \
../src/unittest/TestVector.cpp 

O_SRCS += \
../src/unittest/TestHoudini.o 

OBJS += \
./src/unittest/TestHoudini.o \
./src/unittest/TestVector.o 

CPP_DEPS += \
./src/unittest/TestHoudini.d \
./src/unittest/TestVector.d 


# Each subdirectory must supply rules for building sources it contributes
src/unittest/%.o: ../src/unittest/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


