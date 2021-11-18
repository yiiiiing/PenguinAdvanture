# Programming 3 Exercise project template

1. Make sure you have setup ssh-key for your GitLab account. https://course-gitlab.tuni.fi/profile/keys
2. Clone and add template repo as remote.
Address: git@course-gitlab.tuni.fi:tie-0240x-ohjelmointi-3-programming-3-2020-2021/group_template_project.git
3. Pull from template, and do git submodule update --init in repo. Check that Course now contains something.
4. Make sure you can build the project. (Should compile without issues if your environment is setup correctly)

## Submodule / CourseLib
Submodule for CourseLib is currently configured to use ssh. If you haven't yet setup an ssh-key. Go do it at  https://course-gitlab.tuni.fi/profile/keys

The page contains also instructions for generating and using existing ssh-keys.

Don't change anything in CourseLib ( You won't be able to submit changes made in it )

If you find any bugs and/or missing features you can report them in GitLab https://course-gitlab.tuni.fi/tie-0240x-ohjelmointi-3-programming-3-2020-2021/course/-/issues

## Doxygen documentation

No Doxyfile is provided with the project, but you may generate it using doxygen or doxywizard. For example, "doxygen -g" should generate configuration file named DoxyFile.

## Other notes

You should create your own code inside your own namespace :)


# You are allowed (and probably should) make changes to this file after you have started your project. :)
