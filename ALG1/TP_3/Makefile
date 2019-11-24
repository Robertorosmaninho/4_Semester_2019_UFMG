# Copyright 2018 Roberto Rosmaninho <robertogomes@dcc.ufmg.br>
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.


TARGET := tp3
SRCDIR := src
BUILDDIR := build
INCLUDEDIR := include
BENCHDIR := benchmarks

SRCEXT := cpp
SRC := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT)) 
OBJ := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SRC:.$(SRCEXT)=.o)) 

CC := g++
CPPFLAGS := -g -Wall -std=c++11 -O3
INC := -I $(INCLUDEDIR)/ 

#$(TARGET): $(OBJ)

target: $(TARGET)

$(TARGET): $(OBJ)
						$(CC) $^ -o $(TARGET)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(@D)
	$(CC) $(CPPFLAGS) $(INC) -c -o $@ $<


clean:
	$(RM) -r $(BUILDDIR)/* $(TARGET) 

run:
	$(BENCHDIR)/bench.sh > $(BENCHDIR)/log.txt

.PHONY: clean
