################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../debug/base_types/Particle.cpp 

OBJS += \
./debug/base_types/Particle.o 

CPP_DEPS += \
./debug/base_types/Particle.d 


# Each subdirectory must supply rules for building sources it contributes
debug/base_types/%.o: ../debug/base_types/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


