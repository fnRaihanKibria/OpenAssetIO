#
#   Copyright 2013-2021 The Foundry Visionmongers Ltd
#
#   Licensed under the Apache License, Version 2.0 (the "License");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
#
#       http://www.apache.org/licenses/LICENSE-2.0
#
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an "AS IS" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.
#
"""
Entry point for command-line execution of the manager plugin test
harness.
"""

# pylint: disable=invalid-name

import sys

from openassetio.test.managerValidator import commandLine, validatorSuite


isSuccessful = commandLine.execute(sys.argv, validatorSuite)

sys.exit(int(isSuccessful))