# Basic CI/CD

## Part 1. Setting up the gitlab-runner

* Let's start *Ubuntu server 22.04 LTS* virtual machine.
  * The started virtual machine:
  ![Basic CI/CD](screenshots/vm_version.jpg)

* Let's download and install *gitlab-runner* on the virtual machine.
  * The result of the actions:
  ![Basic CI/CD](screenshots/curl_gitlab_runner.jpg)
  ![Basic CI/CD](screenshots/apt_update.jpg)
  ![Basic CI/CD](screenshots/apt_get_install_gitlab_runner.jpg)

* Let's run *gitlab-runner* and register it for use in the current project.
  * The running *gitlab-runner*:
  ![Basic CI/CD](screenshots/gitlab_runner_start.jpg)

  * The registration *gitlab-runner*:
  ![Basic CI/CD](screenshots/gitlab_runner_register.jpg)

## Part 2. Building

* In the *gitlab-ci.yml* file, add a stage to start the building via *Makefile* from the *C2* project. Save post-build files to a random directory with a 30-day retention period.
  * The build stage is:
  ![Basic CI/CD](screenshots/build_stage.jpg)

  * The build stage success:
  ![Basic CI/CD](screenshots/build_success.jpg)

## Part 3. Codestyle test

* If the codefile didn't pass, `"fail"` the pipeline. In the pipeline, display the output of the *clang-format* utility.
  * The codestyle stage is:
  ![Basic CI/CD](screenshots/codestyle_stage.jpg)

  * The clang-format logs are:
  ![Basic CI/CD](screenshots/clang_format_status.jpg)

  * The codestyle stage success:
  ![Basic CI/CD](screenshots/codestyle_success.jpg)

## Part 4. Integration tests

* Let's run this stage automatically only if the build and codestyle test passes successfully.
If tests didn't pass, `"fail"` the pipeline. In the pipeline, display the output of the succeeded / failed integration tests.
  * The test stage is:
  ![Basic CI/CD](screenshots/test_stage.jpg)

  * The tests logs are:
  ![Basic CI/CD](screenshots/tests_status.jpg)

  * The test stage success:
  ![Basic CI/CD](screenshots/tests_success.jpg)

## Part 5. Deployment stage

* Let's launch the second virtual machine *Ubuntu Server 22.04 LTS*.
  * Two virtual machines:
  ![Basic CI/CD](screenshots/vm_machines.jpg)

* Let's configurate second adapter on all virtual machines.
  * The second adapter configuration:
  ![Basic CI/CD](screenshots/second_adapter.jpg)

* Let's install *netplan* on virtual machines.
  * The installation:
  ![Basic CI/CD](screenshots/set_netplans.jpg)

* Let's configurate virtual machines *netplan* files.
  * The netplans configuration:
  ![Basic CI/CD](screenshots/netplan_configs.jpg)

* Let's check virtual machines connection.
  * The `ping` result:
  ![Basic CI/CD](screenshots/ping_machine.jpg)

* Let's write deploy stage.
  * The deploy stage is:
  ![Basic CI/CD](screenshots/deploy_stage.jpg)

* Let's write deploy script.
  * The deploy script is:
  ![Basic CI/CD](screenshots/deploy_script.jpg)

* Let's generate *ssh-keys* on virtual machines.
  * The generation:
  ![Basic CI/CD](screenshots/ssh_keygens.jpg)

* Let's add the second machine *ssh-key* to *GitLab*.
  * The *ssh-key* on *GitLab*:
  ![Basic CI/CD](screenshots/gitlab_ssh_key.jpg)

* Let's do next actions by `root` to prepare the *pipeline*.
  * Let's add `environment` in *gitlab-runner* `config.toml`:
  ![Basic CI/CD](screenshots/add_env.jpg)

  * Use `key-scan` to save a clone of second virtual machine on the first virtual machine:
  ![Basic CI/CD](screenshots/key_scan.jpg)

  * Copy private *ssh-key* to the first virtual machine:
  ![Basic CI/CD](screenshots/copy_key.png)

  * Use `ssh-copy-id` without `root` to copy key to the second virtual machine:
  ![Basic CI/CD](screenshots/ssh_copy_id.jpg)

  * And restart the *gitlab-runner*:
  ![Basic CI/CD](screenshots/restart_gitlab_runner.jpg)

* Let's make *commit* to check *pipeline*.
  * The *pipeline* work:
  ![Basic CI/CD](screenshots/pipeline_work.jpg)

* Let's check the deploying result.
  * The deploying result:
  ![Basic CI/CD](screenshots/deploy_result.jpg)

## Part 6. Bonus. Notifications

* Let's set up notifications of *successful*/*unsuccessful* *pipeline* execution via bot named `charisel_DO6_CI/CD` in *Telegram*.
  * Write to *BotFather* `start`:
  ![Basic CI/CD](screenshots/talk_bot_father.png)

  * Get from *new_bot* and set it `name` and `username`:
  ![Basic CI/CD](screenshots/prepare_bot.png)

  * Write to *Get My ID* bot `start`:
  ![Basic CI/CD](screenshots/get_my_id_bot.png)

  * Let's launch *notify script* after every stage:
  ![Basic CI/CD](screenshots/notify.jpg)

  * The *notify script* is:
  ![Basic CI/CD](screenshots/notify_script.jpg)

  * The result is:
  ![Basic CI/CD](screenshots/bot_messages.jpg)
