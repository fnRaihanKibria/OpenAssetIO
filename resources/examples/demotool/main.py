from demomanager import DemoManager
from demohost import DemoHost

def main():
    demoManager = DemoManager()
    demoManager.startup()
    demoHost = DemoHost()
    demoHost.startup()
    demoHost.setManager(demoManager)
    demoHost.eventLoop()

if __name__ == '__main__':
    main()
