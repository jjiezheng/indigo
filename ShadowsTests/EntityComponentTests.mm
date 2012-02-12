#import "EntityComponentTests.h"

#include "EntityComponent.h"

@implementation EntityComponentTests

- (void)setUp
{
    [super setUp];
    
    // Set-up code here.
}

- (void)tearDown
{
    // Tear-down code here.
    
    [super tearDown];
}

- (void)testSetsABooleanValueToTrue {
  EntityComponent* component = EntityComponent::component(-1);
  
  std::string test_attr = "test_attr";
  
  component->set_attribute(test_attr, true);  
  BOOLEAN result = component->bool_attribute(test_attr);
  
  STAssertTrue(result, @"component should set boolean attributes");
}

- (void)testSetsABooleanValueToFalse {
  EntityComponent* component = EntityComponent::component(-1);
  
  std::string test_attr = "test_attr";
  
  component->set_attribute(test_attr, false);  
  BOOLEAN result = component->bool_attribute(test_attr);
  
  STAssertFalse(result , @"component should set boolean attributes");
}


@end
