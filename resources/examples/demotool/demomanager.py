from openassetio import constants
from openassetio.managerAPI import ManagerInterface

class DemoManager(ManagerInterface):
    #TODO store setting if this manager supports kWillManagePath

    def startup(self):
        print("DemoManager starting up")

    @staticmethod
    def identifier():
        return "org.openassetio.examples.demomanager"

    def initialize(self, hostSession):
        pass

    def displayName(self):
        return "Demo Asset Manager"

    def info(self):
        return {
            constants.kField_EntityReferencesMatchPrefix: "demo:///"
        }

    def managementPolicy(self, specifications, context, hostSession):
        # pylint: disable=unused-argument
        return [constants.kIgnored for _ in specifications]
