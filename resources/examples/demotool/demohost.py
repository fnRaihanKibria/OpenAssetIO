class DemoHost():
    cmdPrefix = "CMD_"

    def startup(self):
        print("DemoHost starting up")

    def CMD_newProject(self, tokens):
        print("*** Create new project ***")

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
