from demomanager import DemoManagerInterface
from demohost import DemoHost

def main():
    demoHost = DemoHost()
    demoHost.startup()
    demoHost.eventLoop()

if __name__ == '__main__':
    main()
