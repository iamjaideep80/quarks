################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/collisions/Collision.cpp \
../src/collisions/CollisionData.cpp 

OBJS += \
./src/collisions/Collision.o \
./src/collisions/CollisionData.o 

CPP_DEPS += \
./src/collisions/Collision.d \
./src/collisions/CollisionData.d 


# Each subdirectory must supply rules for building sources it contributes
src/collisions/%.o: ../src/collisions/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


