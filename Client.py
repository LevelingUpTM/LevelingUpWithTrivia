import socket
import json
import struct
import time

HOST = 'localhost'
PORT = 5555

class UserClient:
    def __init__(self, host=HOST, port=PORT):
        self.host = host
        self.port = port
        self.sock = None

    def connect(self):
        try:
            self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.sock.connect((self.host, self.port))
            print(f"[+] Connected to {self.host}:{self.port}")
            return True
        except Exception as e:
            print(f"[-] Connection failed: {e}")
            return False

    def send(self, code, data):
        try:
            payload = json.dumps(data).encode('utf-8')  
            header = struct.pack('>BI', code, len(payload))
            self.sock.sendall(header + payload)
            return self.receive()
        except Exception as e:
            print(f"[-] Send error: {e}")
            return None

    def receive(self):
        try:
            header = self._recv_exact(5)
            if not header:
                raise Exception("Failed to receive header.")

            code, length = struct.unpack('>BI', header)
            payload = self._recv_exact(length)
            if not payload:
                raise Exception("Failed to receive payload.")

            response = json.loads(payload.decode('utf-8'))
            return response
        except Exception as e:
            print(f"[-] Receive error: {e}")
            return None

    def _recv_exact(self, num_bytes):
        data = b''
        while len(data) < num_bytes:
            chunk = self.sock.recv(num_bytes - len(data))
            if not chunk:
                return None
            data += chunk
        return data

    def close(self):
        if self.sock:
            self.sock.close()
            self.sock = None
            print("[+] Disconnected.")

def check_login_response(response):
    status = response.get('status')
    if status == 1:
        print("[+] Login SUCCESS")
    elif status == 2:
        print("[-] Login FAILED: User not found")
    elif status == 3:
        print("[-] Login FAILED: Wrong password")
    elif status == 4:
        print("[-] Login FAILED: Already logged in")
    else:
        print("[-] Login FAILED: Unknown status code")

def check_signup_response(response):
    status = response.get('status')
    if status == 1:
        print("[+] Signup SUCCESS")
    elif status == 2:
        print("[-] Signup FAILED: User already exists")
    elif status == 3:
        print("[-] Signup FAILED: Unknown server error")
    else:
        print("[-] Signup FAILED: Unknown status code")

if __name__ == "__main__":
    client = UserClient()

    if client.connect():
        username = "newuser123"
        password = "mypassword"
        email = "newuser123@example.com"

        # First, try to SIGNUP
        signup_data = {
            "username": username,
            "password": password,
            "email": email
        }
        print("\n[*] Attempting signup...")
        signup_response = client.send(2, signup_data)
        if signup_response:
            check_signup_response(signup_response)

        time.sleep(10)

        # Then, try to login
        login_data = {
            "username": username,
            "password": password
        }
        print("\n[*] Attempting login...")
        login_response = client.send(1, login_data)
        if login_response:
            check_login_response(login_response)

        client.close()
