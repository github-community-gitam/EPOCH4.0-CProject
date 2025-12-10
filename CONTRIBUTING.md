# Contributing Guide

Welcome! We’re excited that you want to contribute to this project.  
This guide explains everything you need to know, from forking the repository to getting your pull request merged.

---

## What Does “Contributing” Mean?

Contributing means helping improve the project by:

- Fixing bugs  
- Adding new features **inside the existing programs**  
- Improving documentation  
- Suggesting ideas  
- Cleaning or optimizing code  


---

## Before You Start

### 1️⃣ Fork the Repository  

This creates your own copy of the project in your GitHub account.

### 2️⃣ Clone Your Fork  

Download it to your computer:

```bash
git clone https://github.com/github-community-gitam/EPOCH4.0-CProject.git
```

### 3️⃣ Dependencies  

No dependencies required — this is a pure C project.

---

## Create a New Branch

Before making any changes, create your own branch:

```bash
git checkout -b my-feature
```

Example branch names:

- add-search-feature  
- fix-contact-bug  
- improve-output-format  
- optimize-student-logic  

Branches keep your work organized and separate from the main project.

---

## Make Your Changes

Inside the existing C programs, you may:

- Add new features  
- Improve logic  
- Add structs, functions, pointers  
- Add search or sorting  
- Add file handling  
- Improve menu or output formatting  
- Fix bugs  
- Clean or optimize code  

Keep your changes **small, focused, and clean**.

---

## Test Your Changes

Before committing:

- Compile the program  
- Run it  
- Test your new feature  
- Ensure nothing else breaks  

Manual testing is enough.

---

## Stage Your Changes (git add)

You must stage files before committing.

### Stage ALL changes:

```bash
git add .
```

### Stage ONLY one file:

```bash
git add filename.c
```

Use whichever fits your workflow.

---

## Commit Your Changes

Save your progress with a meaningful commit message:

```bash
git commit -m "Add search feature to Contact Book"
```

❌ Bad:  
update stuff

✅ Good:  
Improve input validation in Student Management System

---

## Push Your Branch

Send your changes to GitHub:

```bash
git push origin my-feature
```

---

## Open a Pull Request (PR)

After pushing your branch:

1. Go to your repository on GitHub  
2. Click **Open Pull Request**  
3. Write a clear description:
   - What you changed  
   - Why you changed it  
   - Any notes for the reviewers  

Clear, well-written PRs are merged faster.

---

## Code Review

A project maintainer will:

- Review your code  
- Suggest improvements (normal!)  
- Approve and merge your PR.  

Don’t worry if you're asked to make changes, it's part of the process.

---

## 🌱 Tips for Beginners

- Don’t fear mistakes — they help you learn  
- Start small  
- Keep pull requests simple  
- Ask for help anytime  
- Write clean commit messages  
- Submit one feature per PR  

---

## Happy coding! 
