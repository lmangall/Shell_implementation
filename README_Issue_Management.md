***Efficient Issue Tracking and Resolution on GitHub***
By following these steps, you can create an issue, label it, fix the issue directly on the main branch, and reference the issue in the commit message. 



**Creating an Issue:**

1. Go to the repository on GitHub.
2. Click on the "Issues" tab.
3. Click the green "New issue" button.
4. Provide a title and description for the issue, explaining the bug.
5. Optionally, use labels to categorize the issue, such as creating a "bug" label.

**Creating a Bug Label:**

1. Visit the "Labels" section of the repository.
2. Click on "New label."
3. Give the label a name like "bug" and choose a color if desired.
4. Save the label.

**Solving the Issue and Writing a Commit:**

- On the main branch, make the necessary code changes to fix the bug.
- Use `git add .` or `git add <file(s)>` to stage the changes.
- Commit the changes with a descriptive message using `git commit -m "Fix issue #47: Description of the fix"`.
- Push the changes directly to the repository's main branch.

**Reference the Issue in the Commit:**

- In the commit message, reference the issue you're fixing by including the issue number. For example: "Fixes #47 - Description of the fix."

**Review and Confirmation:**

- GitHub will automatically recognize the reference in the commit message and link it to the issue.
- The repository maintainers will review the changes and confirm the fix.
- If everything is in order, the fix will be merged into the main branch.
