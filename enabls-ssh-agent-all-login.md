Ubuntu 20.04

sudo apt-get install libpam-ssh
# Add SSH_AUTH_SOCK in /etc/security/pam_env.conf
echo "SSH_AUTH_SOCK DEFAULT=${XDG_RUNTIME_DIR}/ssh-agent.socket" >> /etc/security/pam_env.conf
# disable graphical login
sudo systemctl set-default multi-user.target
