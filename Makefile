# c-linux 统一构建入口（真机 x86_64 上运行）
#   make              编译所有含 main() 的源文件到 build/
#   make run F=a.c    编译并运行指定源文件（默认 leetcode/1_twosum.c）
#   make db           生成 compile_commands.json（供 clangd / Zed 精确补全）
#   make clean        清理

# 显式默认（make 内置 CC=cc 会让 ?= 失效）；命令行可覆盖：make CC=clang
CC       := gcc
CXX      := g++
CPPFLAGS ?= -IMyArray
CFLAGS   ?= -std=c11 -Wall -Wextra -Wpedantic -g -O2
CXXFLAGS ?= -std=c++17 -Wall -Wextra -Wpedantic -g -O2
BUILD    := build

CSRC   := $(wildcard leetcode/*.c MyArray/*.c)
CXXSRC := $(wildcard leetcode/*.cpp)

# 只为含 main() 的源文件生成可执行文件，库文件跳过
MAIN_RE     := ^[[:space:]]*(int|void)[[:space:]]+main[[:space:]]*\(
CSRC_MAIN   := $(shell grep -lE "$(MAIN_RE)" $(CSRC) 2>/dev/null)
CXXSRC_MAIN := $(shell grep -lE "$(MAIN_RE)" $(CXXSRC) 2>/dev/null)
BINS := $(patsubst %,$(BUILD)/%,$(basename $(notdir $(CSRC_MAIN) $(CXXSRC_MAIN))))

.PHONY: all run db clean

all: $(BINS)

$(BUILD):
	@mkdir -p $@

define bin_rule
$(BUILD)/$(basename $(notdir $(1))): $(1) | $(BUILD)
	$(if $(filter %.c,$(1)),$(CC) $(CPPFLAGS) $(CFLAGS),$(CXX) $(CPPFLAGS) $(CXXFLAGS)) $$< -o $$@
endef
$(foreach s,$(CSRC_MAIN) $(CXXSRC_MAIN),$(eval $(call bin_rule,$(s))))

F ?= leetcode/1_twosum.c
run: | $(BUILD)
	@$(MAKE) --no-print-directory $(BUILD)/$(basename $(notdir $(F)))
	@./$(BUILD)/$(basename $(notdir $(F)))

db: | $(BUILD)
	@python3 tools/gen_compile_db.py --cc "$(CC)" --cxx "$(CXX)" \
	  --cflags "$(CPPFLAGS) $(CFLAGS)" --cxxflags "$(CPPFLAGS) $(CXXFLAGS)" \
	  $(CSRC) $(CXXSRC)

clean:
	rm -rf $(BUILD) compile_commands.json
