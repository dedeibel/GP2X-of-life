# 
# This file is part of GP2XOfLife.
# 
# GP2XOfLife is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
# 
# GP2XOfLife is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with GP2XOfLife; if not, write to the Free Software
# Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
# 
# Copyright 2006 Benjamin Peter <BenjaminPeter@arcor.de>
# 

#
#
# Environment
#
#

#DEBUG  = 1
#ASSERT = 1

GP2XDEV=/usr/local/gp2xdev

ifdef TARGET_GP2X
	CHAINPREFIX=$(GP2XDEV)
	CROSS_COMPILE=$(CHAINPREFIX)/bin/gp2x-
else
	CHAINPREFIX=
	CROSS_COMPILE=
endif

CC= $(CROSS_COMPILE)gcc
CXX = $(CROSS_COMPILE)g++

ifdef DEBUG
	STRIP = @echo
else 
	ifdef PROFILE
		STRIP = @echo
	else
		STRIP = $(CROSS_COMPILE)strip
	endif
endif

#
#
# Common options
#
#
CXXFLAGS = -Wold-style-cast -Woverloaded-virtual
#CXXFLAGS = -Weffc++ -Wold-style-cast -Woverloaded-virtual	
CFLAGS   = -Wall

ifdef ASSERT
	CFLAGS += -DASSERT
endif
ifdef DEBUG
	CFLAGS += -DDEBUG -ggdb
endif

#
#
# GP2X Options
#
#

ifdef TARGET_GP2X
	CFLAGS   += -I"$(CHAINPREFIX)/include" `$(CHAINPREFIX)/bin/sdl-config --cflags` \
				-DTARGET_GP2X -msoft-float
	LDFLAGS   = -static -L$(CHAINPREFIX)/lib `$(CHAINPREFIX)/bin/sdl-config --libs` \
				-lSDL_ttf -lfreetype -lSDL

	ifndef DEBUG
		CFLAGS += -O2 -fomit-frame-pointer -ffast-math -funroll-loops
	endif
#
#
# PC Options
#
#
else
	CFLAGS += -I`sdl-config --cflags` -Wall
	LDFLAGS = `sdl-config --libs` -lSDL_ttf -lfreetype -lSDL

	ifndef DEBUG
		CFLAGS += -O2
	endif

	ifdef PROFILE
		CFLAGS  += -pg
		LDFLAGS += -pg
	endif
endif

CXXFLAGS += $(CFLAGS)

#
#
# Build targets
#
#
TARGET = GP2XOfLife.gpe

OBJS = GP2XOfLife.o Game.o World.o Joystick.o GPJoystick.o Keyboard.o Menu.o \
	   WorldDisplay.o NumberDisplay.o

%.o: %.cpp
		$(CXX) $(CXXFLAGS) -c $<

%.o: %.c
		$(CC) $(CFLAGS) -c $<

all: $(TARGET)

$(TARGET): $(OBJS)
		@echo "Linking $(TARGET) ..."
		$(CXX) -o $(TARGET) $(OBJS) $(LDFLAGS)
		$(STRIP) $(TARGET)

package: $(TARGET)
	@echo "Creating package"
	mkdir -p ./tmp/GP2XOfLife
	cp -r font img saves README COPYING GP2XOfLife.gpe ./tmp/GP2XOfLife
	cd ./tmp && zip -r GP2XOfLife.zip GP2XOfLife
	mv tmp/GP2XOfLife.zip .
	rm -rf ./tmp
	@zip -T GP2XOfLife.zip

clean:
		rm -f *.o
		rm -f $(TARGET)
		rm -f GP2XOfLife.zip
