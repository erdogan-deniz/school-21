import yaml  # Module for working with yaml file


def get_yaml_data(file_path: str):  # Get yaml data as data structure
    with open(file_path, 'r') as yaml_file:
        return yaml.safe_load(yaml_file)


def ansible_install_packages_module(install_packages: list):
    return [
        {
            "name": "Install packages",

            "ansible.built.apt":
            {
                "pgk": install_packages,  # If we have than 1 package, then use "pgk" else "name"
                "state": "latest"  # Install last versions
            }
        }
    ]


def ansible_copy_files_module(files: list, file_destination: str):
    return [
        {
            "name": "Copy file",

            "ansible.builtin.copy":
            {
                "src": _,
                "dest": file_destination,
                "mode": "0644"
            }
        }
        for _ in files  # Cycle for taking all files from yaml
    ]


def ansible_run_file_module(script_path: str, bad_guys: list):
    return [
        {
            "name": "Run script",

            "ansible.builtin.script":
            {
                "cmd": f"python3 {script_path}/consumer.py -e {', '.join(bad_guys)}"
            }
        }
    ]


def ansible_generate_data_module(script_path: str):
    return [
        {
            "name": "Run script for generate data",

            "ansible.builtin.script":
            {
                "cmd": f"python3 {script_path}/producer.py -e 2"
            }
        }
    ]


def yaml_save_data(yaml_data, file_src):
    with open(file_src, 'w') as yaml_file:
        yaml.dump(yaml_data, yaml_file, Dumper=yaml.Dumper, sort_keys=False)


if __name__ == "__main__":
    y_data = get_yaml_data("../materials/todo.yml")

    playbook = []
    playbook.extend(ansible_install_packages_module(y_data["server"]["install_packages"]))
    playbook.extend(ansible_copy_files_module(y_data["server"]["exploit_files"], "tmp"))
    playbook.extend(ansible_run_file_module("tmp", y_data["bad_guys"]))
    playbook.extend(ansible_generate_data_module("tmp"))

    yaml_save_data(playbook, "../materials/deploy.yml")
