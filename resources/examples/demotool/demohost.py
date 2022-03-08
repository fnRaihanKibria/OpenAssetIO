class DemoHost():
    cmdPrefix = "CMD_"

    def __init__(self) -> None:
        self.manager = None

    def startup(self):
        print("DemoHost starting up")

    def setManager(self, manager):
        self.manager = manager
        print("DemoHost set manager")

    def CMD_newProject(self, tokens):
        """initialize host with a new project"""
        print("*** Create new project ***")

    def CMD_saveProject(self, tokens):
        """save current project"""
        print("*** Saving current project ***")
        # TODO talk to manager to register this asset

    def CMD_info(self, tokens):
        """show information about the current manager"""
        print("Current manager: {} ({})".format(self.manager.displayName(), self.manager.identifier()))

    def eventLoop(self):
        while(True):
            print("DemoHost>")
            line = input()
            tokens = line.split()
            if len(tokens) == 0:
                continue
            cmd = DemoHost.cmdPrefix + tokens[0]
            if hasattr(self, cmd) and callable(func := getattr(self, cmd)):
                func(tokens)
            else:
                print("Unknown command {}".format(tokens[0]))
