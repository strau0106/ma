GIT_HOOKS_DIR := .git/hooks
HOOK_TYPES := pre-commit
HOOK_SCRIPTS := $(HOOK_TYPES:%=hooks/%)

paper-tex:
	@echo "Building LaTeX paper..."
	cd paper; latexmk main.tex
	@echo "LaTeX paper built successfully."

all: install-hooks

install-hooks: $(HOOK_SCRIPTS)
	@echo "Installing Git hooks..."
	@mkdir -p $(GIT_HOOKS_DIR)
	@for hook in $(HOOK_SCRIPTS); do \
		cp -f $$hook $(GIT_HOOKS_DIR)/$${hook##*/}; \
		chmod +x $(GIT_HOOKS_DIR)/$${hook##*/}; \
	done
	@echo "Git hooks installed successfully."

clean-hooks:
	@echo "Cleaning Git hooks..."
	@for hook in $(HOOK_TYPES); do \
		rm -f $(GIT_HOOKS_DIR)/$$hook; \
	done
	@echo "Git hooks cleaned successfully."

pre-commit: paper-tex
	@cd computer; make runtest
