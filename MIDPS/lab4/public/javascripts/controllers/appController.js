var myApp = angular.module('CoolApp',[]);

myApp.controller('mainController', ['$scope', '$http', function($scope, $http) {
  $http({
    method: 'GET',
    headers: {
      'Accept': 'application/json'
    },
    url: '/preferences'
  }).then(function successCallback(response) {
    console.log("+++++++++++++++++++++")
    console.log(response);
    $scope.preferences = response.data;
    console.log($scope.preferences);
  }, function errorCallback(response) {
    console.log("something is wrong");
  });

  $scope.addPreference = function() {
    if ($scope.preference.name != undefined && $scope.preference.food != undefined) {
      var new_preference = $scope.preference;
      $http({
        method: 'POST',
        url: '/preferences',
        headers: {
          'Accept': 'application/json'
        },
        data: new_preference
      }).then(function successCallback(response) {
        $scope.preferences.unshift(response.data.preference);
        console.log(response.data);
      }, function errorCallback(response) {
        console.log("something is wrong while posting");
      });
      console.log(new_preference);
    }
    $scope.preference = '';
  }

  $scope.removePreference = function() {
    var preference = this.preference;
    $http({
      method: 'DELETE',
      url: '/preferences/' + preference._id,
      headers: {
        'Accept': 'application/json'
      }
    }).then(function successCallback(response) {
      $scope.preferences = $scope.preferences.filter(function(item){
        return item._id != preference._id;
      })
      console.log(response.data);
    }, function errorCallback(response) {
      console.log("something is wrong while posting");
    });
  }
}]);
